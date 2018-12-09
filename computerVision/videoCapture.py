import numpy as np
import cv2 as cv

cap = cv.VideoCapture('checkerboardVideo.mp4')

while(cap.isOpened()):
    ret, frame = cap.read()

    imgHeight = frame.shape[0]
    imgWidth = frame.shape[1]

    resizeIMG = cv.resize(frame,(int(imgWidth/5),int(imgHeight/5)))

    gray = cv.cvtColor(resizeIMG,cv.COLOR_BGR2GRAY)


    ret, thresholdIMG = cv.threshold(gray,127,255,cv.THRESH_BINARY)
    cv.imshow('GreyVideo',gray)
    cv.imshow('thresholdVideo',thresholdIMG)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()
