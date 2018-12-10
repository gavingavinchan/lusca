import numpy as np
import cv2

img = cv2.imread('checkerboard.jpg',0)
#print(img.shape)
#print(img.shape[0])
greyimg = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
cv2.imshow('greyimage',greyimg)
resizeImg = cv2.resize(greyimg,(int(greyimg.shape[1]/2),int(greyimg.shape[0]/2)))
#print(int(img.shape[0]/2),int(img.shape[1]/2))
cv2.imshow('image',resizeImg)

thresholdImg = cv2.threshold(resizeImg,int(greyimg.shape[1]/2),int(greyimg.shape[0]/2),cv2.THRESH_BINARY)
cv2.imshow('binary',thresholdImg)
cv2.waitKey(0)
cv2.destroyAllWindows()
