
# import the necessary packages
import shapedetector
from shapedetector import ShapeDetector
import argparse
import imutils
import cv2
import picamera
import time
import io
import numpy as np

## construct the argument parse and parse the arguments
#ap = argparse.ArgumentParser()
#ap.add_argument("-i", "--image", required=True,
#   help="path to the input image")
#args = vars(ap.parse_args())

## load the image and resize it to a smaller factor so that
## the shapes can be approximated better
image = cv2.imread("/home/pi/Desktop/OutletPics/outletFar.jpg")


#camera = picamera.PiCamera()
#my_file = open("snap.jpg", 'wb')
#camera.start_preview()
#time.sleep(7) # hang for preview for 5 seconds
#camera.capture(my_file)
#camera.stop_preview()
#my_file.close()
#time.sleep(5)
#image = cv2.imread("snap.jpg")

## Create the in-memory stream
#stream = io.BytesIO()
#with picamera.PiCamera() as camera:
#    camera.start_preview()
#    time.sleep(5)
#    camera.capture(stream, format='jpeg')
## Construct a numpy array from the stream
#data = np.fromstring(stream.getvalue(), dtype=np.uint8)
## "Decode" the image from the array, preserving colour
#image = cv2.imdecode(data, 1)
##cv2.imshow("Thresh", image)
##cv2.waitKey(0)

resized = imutils.resize(image, width=300)
ratio = image.shape[0] / float(resized.shape[0])

# convert the resized image to grayscale, blur it slightly,
# and threshold it
gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)

# filter out small lines between counties
kernel = np.ones((5,5),np.float32)/25
gray = cv2.filter2D(gray,-1,kernel)

blurred = cv2.GaussianBlur(gray, (5, 5), 0)


thresh = cv2.threshold(gray, 80, 255, cv2.THRESH_BINARY)[1]
cv2.imshow("Thresh", thresh)
cv2.waitKey(0)

# find contours in the thresholded image and initialize the
# shape detector
cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)
sd = ShapeDetector()

# loop over the contours
for c in cnts:
    # compute the center of the contour, then detect the name of the
    # shape using only the contour
    M = cv2.moments(c)
    cX = int((M["m10"] / M["m00"]) * ratio)
    cY = int((M["m01"] / M["m00"]) * ratio)
    shape = sd.detect(c)
 
    # multiply the contour (x, y)-coordinates by the resize ratio,
    # then draw the contours and the name of the shape on the image
    c = c.astype("float")
    c *= ratio
    c = c.astype("int")
    cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
    cv2.putText(image, shape, (cX, cY), cv2.FONT_HERSHEY_SIMPLEX,
        0.5, (255, 255, 255), 2)
    
    
    resized = imutils.resize(image, width=600)
 
    # show the output image
    cv2.imshow("Image", resized)
    cv2.waitKey(0)

