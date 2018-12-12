import cv2 as cv
import numpy as np

cap = cv.VideoCapture('distortedVideo.mp4')

cvFile = cv.FileStorage("calibrationValues.xml",cv.FILE_STORAGE_READ)
mtx = cvFile.getNode("mtx").mat()
dist = cvFile.getNode("dist").mat()
newCameraMTX = cvFile.getNode("newCameraMTX").mat()

pause = False
while(cap.isOpened()):
    if(pause == False):
        ret, frame = cap.read()

        #imgHeight = frame.shape[0]
        #imgWidth = frame.shape[1]

        #resizeFrame = cv.resize(frame,(int(imgWidth/2),int(imgHeight/2)))

        cv.imshow("original", frame)

        undistortedFrame = cv.undistort(frame,mtx,dist,None,newCameraMTX)
        cv.imshow("undistorted", undistortedFrame)

    key = cv.waitKey(1)
    if key & 0xFF == ord('q'):
        break
    elif key & 0xFF == ord(' '):
        pause = not pause
        print("pause" + str(pause))

cap.release()
cv.destroyAllWindows()
