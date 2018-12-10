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

edgeIMG = cv.Canny(thresholdIMG,100,200,apertureSize = 3)
cv.imshow('edgeIMG',edgeIMG)

'''
lines = cv.HoughLines(edgeIMG,1,np.pi/180,200)
for rho,theta in lines[0]:
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a*rho
    y0 = b*rho
    x1 = int(x0 + 1000*(-b))
    y1 = int(y0 + 1000*(a))
    x2 = int(x0 - 1000*(-b))
    y2 = int(y0 - 1000*(a))

    cv.line(img,(x1,y1),(x2,y2),(0,0,255),2)
cv.imshow('lineIMG',img)
'''

cv.waitKey(0)
cv.destroyAllWindows()
