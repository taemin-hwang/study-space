# From Python
# It requires OpenCV installed for Python
import sys
import cv2
import os
import pyrealsense2 as rs
import numpy as np
from sys import platform
import argparse
import time

def display(datums):
    datum = datums[0]
    cv2.imshow("OpenPose 1.7.0 - Tutorial Python API", datum.cvOutputData)
    key = cv2.waitKey(1)
    return (key == 27)


def printKeypoints(datums):
    datum = datums[0]
    #print("Body keypoints: \n" + str(datum.poseKeypoints))
    #print("Face keypoints: \n" + str(datum.faceKeypoints))
    #print("Left hand keypoints: \n" + str(datum.handKeypoints[0]))
    #print("Right hand keypoints: \n" + str(datum.handKeypoints[1]))

def getBodyCoordinates(datums):
    datum = datums[0]
    if datum.poseKeypoints is None:
        return None
    elif len(datum.poseKeypoints[0][1]) > 2:
        #print("Body keypoints: \n" + str(datum.poseKeypoints[0][1]))
        return datum.poseKeypoints[0][1]
    else: 
        return None

try:
    # Import Openpose (Windows/Ubuntu/OSX)
    dir_path = os.path.dirname(os.path.realpath(__file__))
    try:
        # Windows Import
        if platform == "win32":
            # Change these variables to point to the correct folder (Release/x64 etc.)
            sys.path.append(dir_path + '/../../python/openpose/Release');
            os.environ['PATH']  = os.environ['PATH'] + ';' + dir_path + '/../../x64/Release;' +  dir_path + '/../../bin;'
            import pyopenpose as op
        else:
            # Change these variables to point to the correct folder (Release/x64 etc.)
            sys.path.append('../../python')
            # If you run `make install` (default path is `/usr/local/python` for Ubuntu), you can also access the OpenPose/python module from there. This will install OpenPose and the python library at your desired installation path. Ensure that this is in your python path in order to use it.
            # sys.path.append('/usr/local/python')
            from openpose import pyopenpose as op
    except ImportError as e:
        print('Error: OpenPose library could not be found. Did you enable `BUILD_PYTHON` in CMake and have this Python script in the right folder?')
        raise e

    # Flags
    parser = argparse.ArgumentParser()
    parser.add_argument("--no-display", action="store_true", help="Disable display.")
    args = parser.parse_known_args()

    # Custom Params (refer to include/openpose/flags.hpp for more parameters)
    params = dict()
    params["model_folder"] = "../../../models/"

    # Add others in path?
    for i in range(0, len(args[1])):
        curr_item = args[1][i]
        if i != len(args[1])-1: next_item = args[1][i+1]
        else: next_item = "1"
        if "--" in curr_item and "--" in next_item:
            key = curr_item.replace('-','')
            if key not in params:  params[key] = "1"
        elif "--" in curr_item and "--" not in next_item:
            key = curr_item.replace('-','')
            if key not in params: params[key] = next_item

    # Construct it from system arguments
    # op.init_argv(args[1])
    # oppython = op.OpenposePython()

    # Starting OpenPose
    opWrapper = op.WrapperPython(op.ThreadManagerMode.AsynchronousOut)
    opWrapper.configure(params)
    opWrapper.start()

    # Create a context object. This object owns the handles to all connected realsense devices
    pipeline = rs.pipeline()

    # Configure streams
    config = rs.config()
    config.enable_stream(rs.stream.depth, 1280, 720, rs.format.z16, 30)

    # Start streaming
    pipeline.start(config)

    # Main loop
    userWantsToExit = False
    while not userWantsToExit:
        # This call waits until a new coherent set of frames is available on a device
        # Calls to get_frame_data(...) and get_frame_timestamp(...) on a device will return stable values until wait_for_frames(...) is called
        frames = pipeline.wait_for_frames()
        depth = frames.get_depth_frame()
        if not depth: continue

        # Pop frame
        #time.sleep(0.01)
        datumProcessed = op.VectorDatum()
        if opWrapper.waitAndPop(datumProcessed):
            if not args[0].no_display:
                # Display image
                userWantsToExit = display(datumProcessed)
            printKeypoints(datumProcessed)
            bodyXYcoordinates = getBodyCoordinates(datumProcessed)
            if bodyXYcoordinates is not None:
                #print("Body coordinates : " + str(bodyXYcoordinates[0]) + ", " + str(bodyXYcoordinates[1]))
                dist = depth.get_distance(bodyXYcoordinates[0], bodyXYcoordinates[1])
                if dist > 0: print("Distance : " + str(dist) + " (m)")
        else:
            break
except Exception as e:
    print(e)
    sys.exit(-1)

