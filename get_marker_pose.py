import picamera
import cv2 as cv

camera = picamera.PiCamera()
rawCapture = PiRGBArray(camera)

# Path to file with the camera calibration params
calibrationFileName = 'camera_param.yaml'

# Retrieve the camera calibration
calibFile = cv.FileStorage(calibrationFileName, cv.FILE_STORAGE_READ)
camMatrix = calibFile.getNode('camera_matrix').mat()
distMatrix = calibFile.getNode('dist_coeff').mat()
calibFile.release()

while True:
    # (ret, frame) = webcam.read()
    camera.capture(rawCapture, format='bgr')
    frame = rawCapture.array
    grayImg = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    arucoDict = aruco.Dictionary_get(aruco.DICT_4X4_250)
    params = aruco.DetectorParameters_create()

    (corners, ids, rejectedImgPoints) = aruco.detectMarkers(grayImg, arucoDict, parameters=params)

    if np.all(ids != None):
        (rotVec, transVec, _) = aruco.estimatePoseSingleMarkers(corners, 0.05, camMatrix, distMatrix)
        for trans, rot in zip(transVec, rotVec):
            print('Translation: {}. Rotation: {}'.format(trans, rot), end='\r')
            # Only save detections from the first marker, we're assuming there isn't more than one
            # Robot coordinate frame: x axis is defined by where the camera is pointing
            xTranslation = trans[0][2]
            yTranslation = trans[0][0]
            wallRotation = rot[0][2]
