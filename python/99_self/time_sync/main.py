import numpy as np
import cv2
import os.path
import threading
import time
import datetime
from queue import Queue, PriorityQueue

import file_storage as fs

cam_num_ = 4
min_cam_ = 2
time_delta_ = 50 # milli-seconds
target_fps_ = 1000/time_delta_

mq_ = PriorityQueue()
lk_ = threading.Lock()

def get_initial_matching_table(cams):
    matching_table = {}
    for cam_id in range(1, cam_num_+1):
        matching_table[str(cam_id)] = {}
        matching_table[str(cam_id)]['is_valid'] = False
        matching_table[str(cam_id)]['keypoint'] = np.zeros((25, 3))
        matching_table[str(cam_id)]['P'] = cams[str(cam_id)]['P']
    return matching_table

def reset_matching_table(matching_table):
    for cam_id in range(1, cam_num_+1):
        matching_table[str(cam_id)] = {}
        matching_table[str(cam_id)]['is_valid'] = False

def get_test_table(cams):
    matching_table = {}
    for cam_id in range(1, cam_num_-1):
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
    valid_dlt_element['valid_keypoint'] = []
    valid_dlt_element['valid_P'] = []

    for cam_id in range(1, cam_num_+1):
        if matching_table[str(cam_id)]['is_valid'] is True:
            valid_dlt_element['count'] += 1
            valid_dlt_element['valid_keypoint'].append(matching_table[str(cam_id)]['keypoint'])
            valid_dlt_element['valid_P'].append(matching_table[str(cam_id)]['P'])

    return valid_dlt_element

def set_matching_table(mq, lk, matching_table):
    lk.acquire()
    qsize = mq.qsize()

    print('=======================================================')
    for i in range(qsize):
        data = mq.get()
        print(data)
        # break, if timestamp not exist between valid range
        # update, if timestamp exist between valid range
    print('=======================================================')

    lk.release()

def restore_3d_pose():
    param_dir = './etc/'
    intri_path = param_dir+'intri.yml'
    extri_path = param_dir+'extri.yml'
    cams = fs.read_camera(intri_path, extri_path)
    #fs.print_camera_parameter(cams)

    matching_table = get_test_table(cams)
    #matching_table = get_initial_matching_table(cams)

    while True:
        set_matching_table(mq_, lk_, matching_table)
        valid_dlt_element = get_valid_dlt_element(matching_table)

        if valid_dlt_element['count'] >= min_cam_:
            print('Try to restore 3D pose')
            valid_keypoint = np.stack(valid_dlt_element['valid_keypoint'], axis=0)
            valid_p = np.stack(valid_dlt_element['valid_P'], axis=0)
            #out = batch_triangulation(valid_keypoint, valid_p)
            reset_matching_table(matching_table)
        else:
            print('Skip to restore 3D pose, number of valid data is ', valid_dlt_element['count'])

        time.sleep(10/1000)

import random

def test_work_cam1(mq, lk):
    while True:
        lk.acquire()
        r = random.random()
        r_diff = r/20
        timestamp = datetime.datetime.now().timestamp() + r_diff

        mq.put((timestamp, [1]))
        lk.release()
        time.sleep(60/1000)

def test_work_cam2(mq, lk):
    while True:
        lk.acquire()
        r = random.random()
        r_diff = r/10
        timestamp = datetime.datetime.now().timestamp() + r_diff

        mq.put((timestamp, [2]))
        lk.release()
        time.sleep(20/1000)

def test_work_cam3(mq, lk):
    while True:
        lk.acquire()
        r = random.random()
        r_diff = r/50
        timestamp = datetime.datetime.now().timestamp() + r_diff

        mq.put((timestamp, [3]))
        lk.release()
        time.sleep(100/1000)

def test_work_cam4(mq, lk):
    while True:
        lk.acquire()
        r = random.random()
        r_diff = r/100
        timestamp = datetime.datetime.now().timestamp() + r_diff

        mq.put((timestamp, [4]))
        lk.release()
        time.sleep(50/1000)

t1 = threading.Thread(target=test_work_cam1, args=(mq_, lk_))
t2 = threading.Thread(target=test_work_cam2, args=(mq_, lk_))
t3 = threading.Thread(target=test_work_cam3, args=(mq_, lk_))
t4 = threading.Thread(target=test_work_cam4, args=(mq_, lk_))
t5 = threading.Thread(target=restore_3d_pose)
t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t5.join()

