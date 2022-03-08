import numpy as np
import cv2
import os.path
import threading
import time
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

def get_3d_pose_estimation(valid_dlt_element):
    if valid_dlt_element['count'] >= min_cam_:
        print('Try to restore 3D pose')
        valid_keypoint = np.stack(valid_dlt_element['valid_keypoint'], axis=0)
        valid_p = np.stack(valid_dlt_element['valid_P'], axis=0)
        #out = batch_triangulation(valid_keypoint, valid_p)
    else:
        print('Skip to restore 3D pose, number of valid data is ', valid_dlt_element['count'])

def set_matching_table(mq, lk, matching_table):
    lk.acquire()
    qsize = mq.size()

    for i in range(qsize):
        data = mq.get()
        # break, if timestamp not exist between valid range
        # update, if timestamp exist between valid range

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
        valid_dlt_element = get_valid_dlt_element(matching_table)
        get_3d_pose_estimation(valid_dlt_element)
        time.sleep(0.2*time_delta_/1000)

def make_smooth_with_confidence():
    print('Make motion smooth with interpolation')

t1 = threading.Thread(target=restore_3d_pose)
t1.start()
t1.join()

