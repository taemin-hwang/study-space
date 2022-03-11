import numpy as np
import cv2
import os.path
import threading
import time
import datetime
from queue import Queue, PriorityQueue

from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt

import file_storage as fs
import skeleton_sender as ss

cam_num_ = 4
min_cam_ = 2
min_confidence_ = 0.4
time_delta_ = 40 # milli-seconds
target_fps_ = 1000/time_delta_
buffer_size_ = 5

#mq_ = PriorityQueue()
mq_ = Queue()
lk_ = threading.Lock()

def get_initial_matching_table(cams):
    matching_table = {}
    for cam_id in range(1, cam_num_+1):
        matching_table[str(cam_id)] = {}
        matching_table[str(cam_id)]['is_valid'] = False
        matching_table[str(cam_id)]['timestamp'] = 0
        matching_table[str(cam_id)]['keypoint'] = np.zeros((25, 3))
        matching_table[str(cam_id)]['P'] = cams[str(cam_id)]['P']
    return matching_table

def reset_matching_table(matching_table):
    for cam_id in range(1, cam_num_+1):
        matching_table[str(cam_id)]['is_valid'] = False

def get_test_table(cams):
    matching_table = {}
    for cam_id in range(1, 3):
        matching_table[str(cam_id)] = {}
        matching_table[str(cam_id)]['is_valid'] = False
        matching_table[str(cam_id)]['keypoint'] = np.zeros((25, 3))
        matching_table[str(cam_id)]['P'] = cams[str(cam_id)]['P']

    matching_table[str(3)] = {}
    matching_table[str(3)]['is_valid'] = True
    matching_table[str(3)]['keypoint'] = np.ones((25, 3))
    matching_table[str(3)]['P'] = cams[str(3)]['P']

    matching_table[str(4)] = {}
    matching_table[str(4)]['is_valid'] = True
    matching_table[str(4)]['keypoint'] = np.ones((25, 3))
    matching_table[str(4)]['P'] = cams[str(4)]['P']
    return matching_table

def get_valid_dlt_element(matching_table):
    valid_dlt_element = {}
    valid_dlt_element['count'] = 0
    valid_dlt_element['valid_timestamp'] = []
    valid_dlt_element['valid_keypoint'] = []
    valid_dlt_element['valid_P'] = []

    for cam_id in range(1, cam_num_+1):
        if matching_table[str(cam_id)]['is_valid'] is True:
            #print(matching_table[str(cam_id)])
            valid_dlt_element['count'] += 1
            valid_dlt_element['valid_timestamp'].append(matching_table[str(cam_id)]['timestamp'])
            valid_dlt_element['valid_keypoint'].append(matching_table[str(cam_id)]['keypoint'])
            valid_dlt_element['valid_P'].append(matching_table[str(cam_id)]['P'])

    return valid_dlt_element

def sync_matching_table(mq, lk, matching_table, t_start, t_end, t_diff):
    lk.acquire()
    qsize = mq.qsize()

    if qsize > min_cam_:
        for i in range(qsize):
            data = mq.get()
            t = data[0]
            if t_start == -1:
                t_start = data[0]
                t_end = data[0] + time_delta_/1000
                t_diff = datetime.datetime.now().timestamp() - t_start
            elif t < t_start:
                continue
            elif t > t_end:
                mq.put(data)
            else:
                cam_id = data[1]['id']
                timestamp = data[1]['timestamp']
                keypoints = data[1]['keypoints']
                matching_table[str(cam_id)]['is_valid'] = True
                matching_table[str(cam_id)]['timestamp'] = timestamp
                matching_table[str(cam_id)]['keypoint'] = keypoints
    lk.release()
    return (t_start, t_end, t_diff)

def use_previous_frame(matching_table, t_start, t_end):
    for cam_id in range(1, cam_num_+1):
        if matching_table[str(cam_id)]['is_valid'] is False:
            if t_start - matching_table[str(cam_id)]['timestamp'] < time_delta_*4:
                matching_table[str(cam_id)]['is_valid'] = True

def use_latest_matching_table(mq, lk, matching_table):
    lk.acquire()
    qsize = mq.qsize()

    for i in range(qsize):
        data = mq.get()
        cam_id = data[1]['id']
        timestamp = data[1]['timestamp']
        keypoints = data[1]['keypoints']
        matching_table[str(cam_id)]['is_valid'] = True
        matching_table[str(cam_id)]['timestamp'] = timestamp
        matching_table[str(cam_id)]['keypoint'] = keypoints
    lk.release()

def is_time_expired(t_start, t_end, t_diff):
    if t_end - t_diff >= datetime.datetime.now().timestamp():
        return True
    else:
        return False

def get_initial_time():
    t_start = -1
    t_end = -1
    t_diff = 0
    return (t_start, t_end, t_diff)

def reset_time(t):
    t_start = t[0]
    t_end = t[1]
    t_diff = t[2]
    if t_start != -1:
        t_start = t_end
        t_end = t_start + time_delta_/1000
    return (t_start, t_end, t_diff)

def batch_triangulate(keypoints_, Pall):
    # keypoints: (nViews, nJoints, 3)
    # Pall: (nViews, 3, 4)
    # A: (nJoints, nViewsx2, 4), x: (nJoints, 4, 1); b: (nJoints, nViewsx2, 1)
    v = (keypoints_[:, :, -1]>0).sum(axis=0)
    valid_joint = np.where(v > 1)[0]
    keypoints = keypoints_[:, valid_joint]
    conf3d = keypoints[:, :, -1].sum(axis=0)/v[valid_joint]
    # P2: last row of matrix：(1, nViews, 1, 4)
    P0 = Pall[None, :, 0, :]
    P1 = Pall[None, :, 1, :]
    P2 = Pall[None, :, 2, :]

    # uP2: The x coordinate is multiplied by P2: (nJoints, nViews, 1, 4)
    uP2 = keypoints[:, :, 0].T[:, :, None] * P2
    vP2 = keypoints[:, :, 1].T[:, :, None] * P2
    conf = keypoints[:, :, 2].T[:, :, None]
    Au = conf * (P0 - uP2)
    Av = conf * (vP2 - P1)
    A = np.hstack([Au, Av])

    u, s, v = np.linalg.svd(A)
    X = v[:, -1, :]
    X = X / X[:, 3:]
    # out: (nJoints, 4)
    result = np.zeros((keypoints_.shape[1], 4))
    result[valid_joint, :3] = X[:, :3]
    result[valid_joint, 3] = conf3d
    return result


def restore_3d_pose(enable_sync):
    param_dir = './etc/'
    intri_path = param_dir+'intri.yml'
    extri_path = param_dir+'extri.yml'
    cams = fs.read_camera(intri_path, extri_path)
    #fs.print_camera_parameter(cams)
    sender = ss.SkeletonSender()

    matching_table = get_initial_matching_table(cams)
    t = get_initial_time()

    print('Time synchronization : ', enable_sync)

    frame_buffer = np.ones((buffer_size_, 25, 4))
    ret = np.zeros((25, 4))

    while True:
        if enable_sync is True:
            t = sync_matching_table(mq_, lk_, matching_table, t[0], t[1], t[2])
            use_previous_frame(matching_table, t[0], t[1])
        else:
            use_latest_matching_table(mq_, lk_, matching_table)

        valid_dlt_element = get_valid_dlt_element(matching_table)
        print(valid_dlt_element['valid_timestamp'])
        if valid_dlt_element['count'] >= min_cam_:
            print('Try to restore 3D pose with ', valid_dlt_element['count'], 'cameras')
            valid_keypoint = np.stack(valid_dlt_element['valid_keypoint'], axis=0)
            valid_p = np.stack(valid_dlt_element['valid_P'], axis=0)
            out = batch_triangulate(valid_keypoint, valid_p)

            # moving average
            frame_buffer = np.roll(frame_buffer, -1, axis=0)
            frame_buffer[buffer_size_-1] = out

            for i in range(out.shape[0]):
                parts = frame_buffer[:, i, :]
                xdata = parts[:, 0]
                ydata = parts[:, 1]
                zdata = parts[:, 2]
                cdata = parts[:, 3]*100

                if np.sum(cdata) < 0.01:
                    break

                #print('xdata :', xdata)
                #print('ydata :', ydata)
                #print('zdata :', zdata)
                #print('cdata :', cdata)

                x_avg = np.average(xdata, weights=cdata)
                y_avg = np.average(ydata, weights=cdata)
                z_avg = np.average(zdata, weights=cdata)
                c_avg = np.average(cdata, weights=cdata)
                ret[i] = [x_avg, y_avg, z_avg, c_avg/100]

            # send 3d skeleton
            ret[:, 0] = -1*ret[:, 0]
            ret[:, 1] = -1*ret[:, 1]
            ret[:, 2] = -1*ret[:, 2]
            ret[:, 3][ret[:, 3] < min_confidence_] = 0
            sender.send_3d_skeletons(ret)

            reset_matching_table(matching_table)
        else:
            print('Skip to restore 3D pose, number of valid data is ', valid_dlt_element['count'])

        reset_matching_table(matching_table)
        t = reset_time(t)

        time.sleep(time_delta_/1000)

import random
import json

def test_work_cam1(mq, lk):
    cam_id = 1
    for frame_id in range(5, 1799):
        filename = str(frame_id).zfill(6) + '.json'
        directory = './annots/' + str(cam_id) + '/'
        with open(directory+filename, "r") as json_file:
            json_data = json.load(json_file)
            keypoints = np.array(json_data['annots'][0]['keypoints'])

        timestamp = datetime.datetime.now().timestamp() + frame_id*20/1000

        lk.acquire()
        mq.put((timestamp, {'id': 1, 'timestamp': timestamp, 'keypoints': keypoints}))
        lk.release()

        r = random.random()
        r -= 0.5
        #r_diff = r/40
        r_diff = r * time_delta_ / 2 / 1000
        time.sleep(time_delta_/1000 + r_diff)

def test_work_cam2(mq, lk):
    cam_id = 2
    for frame_id in range(5, 1799):
        filename = str(frame_id).zfill(6) + '.json'
        directory = './annots/' + str(cam_id) + '/'
        with open(directory+filename, "r") as json_file:
            json_data = json.load(json_file)
            keypoints = np.array(json_data['annots'][0]['keypoints'])

        timestamp = datetime.datetime.now().timestamp() + frame_id*20/1000

        lk.acquire()
        mq.put((timestamp, {'id': 2, 'timestamp': timestamp, 'keypoints': keypoints}))
        lk.release()

        r = random.random()
        r -= 0.5
        #r_diff = r/40
        r_diff = r * time_delta_ / 2 / 1000
        time.sleep(time_delta_/1000 + r_diff)

def test_work_cam3(mq, lk):
    cam_id = 3
    for frame_id in range(5, 1799):
        filename = str(frame_id).zfill(6) + '.json'
        directory = './annots/' + str(cam_id) + '/'
        with open(directory+filename, "r") as json_file:
            json_data = json.load(json_file)
            keypoints = np.array(json_data['annots'][0]['keypoints'])

        timestamp = datetime.datetime.now().timestamp() + frame_id*20/1000

        lk.acquire()
        mq.put((timestamp, {'id': 3, 'timestamp': timestamp, 'keypoints': keypoints}))
        lk.release()

        r = random.random()
        r -= 0.5
        #r_diff = r/40
        r_diff = r * time_delta_ / 2 / 1000
        time.sleep(time_delta_/1000 + r_diff)

def test_work_cam4(mq, lk):
    cam_id = 4
    for frame_id in range(5, 1799):
        filename = str(frame_id).zfill(6) + '.json'
        directory = './annots/' + str(cam_id) + '/'
        with open(directory+filename, "r") as json_file:
            json_data = json.load(json_file)
            keypoints = np.array(json_data['annots'][0]['keypoints'])

        timestamp = datetime.datetime.now().timestamp() + frame_id*20/1000

        lk.acquire()
        mq.put((timestamp, {'id': 4, 'timestamp': timestamp, 'keypoints': keypoints}))
        lk.release()

        r = random.random()
        r -= 0.5
        r_diff = r * time_delta_ / 2 / 1000
        time.sleep(time_delta_/1000 + r_diff)

import sys

enable_sync = True
if sys.argv.count('-nosync'):
    enable_sync = False
elif sys.argv.count('-nonsync'):
    enable_sync = False
elif sys.argv.count('nonsync'):
    enable_sync = False
else:
    enable_sync = True

t1 = threading.Thread(target=test_work_cam1, args=(mq_, lk_))
t2 = threading.Thread(target=test_work_cam2, args=(mq_, lk_))
t3 = threading.Thread(target=test_work_cam3, args=(mq_, lk_))
t4 = threading.Thread(target=test_work_cam4, args=(mq_, lk_))
t5 = threading.Thread(target=restore_3d_pose, args=((enable_sync,)))

t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t5.join()

