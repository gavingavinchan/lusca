import numpy as np
import cv2 as cv

cap = cv.VideoCapture('checkerboardVideo.mp4')

while(cap.isOpened()):
    ret, frame = cap.read()

    imgHeight = frame.shape[0]
    imgWidth = frame.shape[1]

    resizeIMG = cv.resize(frame,(int(imgWidth/5),int(imgHeight/5)))

    gray = cv.cvtColor(resizeIMG,cv.COLOR_BGR2GRAY)
    cv.imshow('GreyVideo',gray)

    blurIMG = cv.blur(resizeIMG,(5,5))
    cv.imshow("blurVideo",blurIMG)

    ret, thresholdIMG = cv.threshold(blurIMG,60,255,cv.THRESH_BINARY)
    cv.imshow('thresholdVideo',thresholdIMG)

    kernel = np.ones((5,5),np.uint8)
    closingIMG = cv.morphologyEx(thresholdIMG,cv.MORPH_CLOSE,kernel)

    edgeIMG = cv.Canny(closingIMG,100,200)
    cv.imshow('edgeIMG',edgeIMG)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv.destroyAllWindows()
