import numpy as np
import cv2 as cv

resizeValue = 0.2

cap = cv.VideoCapture('checkerboardVideo.mp4')

ret = True
while(ret and cap.isOpened()):
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

    ret, frame = cap.read()

    if(ret == False):
        break

    imgHeight, imgWidth, layers  = frame.shape

    resizeIMG = cv.resize(frame,(int(imgWidth*resizeValue),int(imgHeight*resizeValue)))

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

    print('in video loop')



print('out of video loop')

cap.release()
cv.destroyAllWindows()
