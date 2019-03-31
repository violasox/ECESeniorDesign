import picamera
import cv2.aruco as aruco
from picamera.array import PiRGBArray
import cv2 as cv
import numpy as np
import time
import serial
import sys

displayImage = True
ser = serial.Serial('/dev/ttyACM0') 
camera = picamera.PiCamera()
#camera.resolution(640, 480)
camera.resolution = (640, 480)
rawCapture = PiRGBArray(camera, size=(640, 480))

# Path to file with the camera calibration params
calibrationFileName = '/home/pi/ECESeniorDesign/camera_param.yaml'

# Retrieve the camera calibration
calibFile = cv.FileStorage(calibrationFileName, cv.FILE_STORAGE_READ)
camMatrix = calibFile.getNode('camera_matrix').mat()
distMatrix = calibFile.getNode('dist_coeff').mat()
calibFile.release()
arucoDict = aruco.Dictionary_get(aruco.DICT_4X4_250)
params = aruco.DetectorParameters_create()
print('initialized')

while True:
    # beginCaptureTime = time.time()
    camera.capture(rawCapture, format='bgr')
    frame = rawCapture.array
    grayImg = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    (corners, ids, rejectedImgPoints) = aruco.detectMarkers(grayImg, arucoDict, parameters=params)

    if np.all(ids != None):
        (rotVec, transVec, _) = aruco.estimatePoseSingleMarkers(corners, 0.05, camMatrix, distMatrix)
        for trans, rot in zip(transVec, rotVec):
            print('Translation: {}. Rotation: {}'.format(trans*1000, rot*1000), end='\r')
            # Only save detections from the first marker, we're assuming there isn't more than one
            # Robot coordinate frame: x axis is defined by where the camera is pointing
            xTranslation = trans[0][2]
            xTranslation = xTranslation*1000
            yTranslation = trans[0][0]
            yTranslation = yTranslation*1000
            wallRotation = rot[0][2]
            wallRoation = wallRotation*1000
            
            sendStr = '{},{},{},{}'.format(xTranslation, yTranslation, wallRotation,"\n")
            sendStr = sendStr.encode('utf-8')
            ser.write(sendStr)
            
    #if displayImage:
        #cv.imshow('frame', frame)

    rawCapture.truncate(0)
    # elapsedCaptureTime = time.time() - beginCaptureTime
    # print(elapsedCaptureTime)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
    # Flush output so we can see the log while the process is running
    sys.stdout.flush()
