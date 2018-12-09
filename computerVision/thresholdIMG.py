import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

img = cv.imread('checkerboardIMG.jpg',cv.IMREAD_GRAYSCALE)

imgHeight = img.shape[0]
imgWidth = img.shape[1]

#print(img.shape)
#ret,thresh = cv.threshold(img,)
#cv.imshow('image',img)

resizeIMG = cv.resize(img,(int(imgWidth/5),int(imgHeight/5)))

ret, thresholdIMG = cv.threshold(resizeIMG,127,255,cv.THRESH_BINARY)

cv.imshow('image',thresholdIMG)

cv.waitKey(0)
cv.destroyAllWindows()
