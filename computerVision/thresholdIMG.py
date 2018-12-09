import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

img = cv.imread('checkerboardIMG.jpg',cv.IMREAD_GRAYSCALE)

imgHeight = img.shape[0]
imgWidth = img.shape[1]

#print(img.shape)
#ret,thresh = cv.threshold(img,)
#cv.imshow('image',img)

resizeIMG = cv.resize(img,(int(imgWidth/10),int(imgHeight/10)))
cv.imshow('resizedIMG',resizeIMG)

blurIMG = cv.blur(resizeIMG,(5,5))
cv.imshow('blurIMG',blurIMG)

ret, thresholdIMG = cv.threshold(blurIMG,127,255,cv.THRESH_BINARY)
cv.imshow('thresholdIMG',thresholdIMG)

edgeIMG = cv.Canny(thresholdIMG,100,200)
cv.imshow('edgeIMG',edgeIMG)

cv.waitKey(0)
cv.destroyAllWindows()
