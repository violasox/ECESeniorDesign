import cv2 as cv
import cv2.aruco as aruco
import numpy as np

# Might need to adjust this based on your computer
webcam = cv.VideoCapture(0)

# Path to file with the camera calibration params
calibrationFileName = 'camera_param.yaml'

# Retrieve the camera calibration
calibFile = cv.FileStorage(calibrationFileName, cv.FILE_STORAGE_READ)
camMatrix = calibFile.getNode('camera_matrix').mat()
distMatrix = calibFile.getNode('dist_coeff').mat()
calibFile.release()

# Font for displaying the marker stuff
font = cv.FONT_HERSHEY_SIMPLEX

while True:
    (ret, frame) = webcam.read()
    grayImg = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    arucoDict = aruco.Dictionary_get(aruco.DICT_4X4_250)
    params = aruco.DetectorParameters_create()

    (corners, ids, rejectedImgPoints) = aruco.detectMarkers(grayImg, arucoDict, parameters=params)

    if np.all(ids != None):
        (rotVec, transVec, _) = aruco.estimatePoseSingleMarkers(corners, 0.05, camMatrix, distMatrix)
        for i in range(ids.size):
            aruco.drawAxis(frame, camMatrix, distMatrix, rotVec[i], transVec[i], 0.1)
        aruco.drawDetectedMarkers(frame, corners)

    else:
        cv.putText(frame, "No Ids", (0,64), font, 1, (0,255,0), 2, cv.LINE_AA)

    cv.imshow('frame', frame) 
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
