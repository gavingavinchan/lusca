import cv2 as cv
import numpy as np

resizeValue = 1.5

cap = cv.VideoCapture(0)

cvFile = cv.FileStorage("calibrationValues.xml",cv.FILE_STORAGE_READ)
mtx = cvFile.getNode("mtx").mat()
dist = cvFile.getNode("dist").mat()
newCameraMTX = cvFile.getNode("newCameraMTX").mat()

pause = False
while(cap.isOpened()):
    if(pause == False):
        ret, frame = cap.read()

        imgHeight, imgWidth, layers = frame.shape

        resizeIMG = cv.resize(frame,(int(imgWidth*resizeValue),int(imgHeight*resizeValue)))

        cv.imshow("original", resizeIMG)

        undistortedFrame = cv.undistort(resizeIMG,mtx,dist,None,newCameraMTX)
        cv.imshow("undistorted", undistortedFrame)

    key = cv.waitKey(1)
    if key & 0xFF == ord('q'):
        break
    elif key & 0xFF == ord(' '):
        pause = not pause
        print("pause " + str(pause))

cap.release()
cv.destroyAllWindows()
