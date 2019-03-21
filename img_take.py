# app.py
import time
import cv2
import picamera

camera = picamera.PiCamera()
camera.start_preview()
time.sleep(7) # hang for preview for 5 seconds
camera.capture('/home/pi/Desktop/snapshot.jpg')
camera.stop_preview()
