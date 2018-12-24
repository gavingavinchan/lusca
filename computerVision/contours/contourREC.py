import cv2 as cv
import numpy as np

img = cv.imread('line1.jpg',0) #grey

imgHeight = img.shape[0]
imgWidth = img.shape[1]

resizeIMG = cv.resize(img,(int(imgWidth/10),int(imgHeight/10)))
cv.imshow('resizedIMG',resizeIMG)

blur = cv.blur(resizeIMG,(5,5))
thresh = cv.adaptiveThreshold(blur,255,cv.ADAPTIVE_THRESH_GAUSSIAN_C,cv.THRESH_BINARY_INV,11,2)
cv.imshow('thresh',thresh)


#blur with gaussianblur
blurGaussian = cv.GaussianBlur(resizeIMG, (5,5),0)
ret,threshG = cv.threshold(blur,0,255,cv.THRESH_BINARY_INV+cv.THRESH_OTSU)
cv.imshow('threshG',threshG)

imgContour,contours, hierarchy = cv.findContours(threshG,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
contoursIMG = cv.drawContours(resizeIMG, contours, -1,(255,255,255),2)
cv.imshow('contoursIMG',contoursIMG)




cv.waitKey(0)
cv.destroyAllWindows()
