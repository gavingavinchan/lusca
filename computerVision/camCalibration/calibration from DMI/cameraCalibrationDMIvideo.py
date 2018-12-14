import cv2 as cv
import numpy as np

resizeValue = 1


x,y = np.meshgrid(range(7),range(6))
worldPoints = np.hstack((x.reshape(42,1),y.reshape(42,1),np.zeros((42,1)))).astype(np.float32)


objPoints = []
imgPoints =[]
numberOfFramesUsed = 0

cap = cv.VideoCapture('distortedVideo.mp4')

imgWidth = 0
imgHeight = 0


ret = True
pause = False
while(ret and cap.isOpened()):
    key = cv.waitKey(1)

    if key & 0xFF == ord('q'):
        break
    elif key & 0xFF == ord(' '):
        pause = not pause
        print("pause" + str(pause))

    if(pause == False):
        ret, frame = cap.read()

        if(ret == False):
            break

        imgHeight, imgWidth, layers  = frame.shape

        resizeIMG = cv.resize(frame,(int(imgWidth*resizeValue),int(imgHeight*resizeValue)))

        retCorner, corners = cv.findChessboardCorners(resizeIMG, (7,6))


        if retCorner:
            numberOfFramesUsed += 1

            corners = corners.reshape(-1,2)

            frame_vis = frame.copy()
            cv.drawChessboardCorners(frame_vis, (7,6), corners, ret)
            cv.imshow(str(numberOfFramesUsed), frame_vis)
            imgPoints.append(corners)
            objPoints.append(worldPoints)

        else:
            cv.imshow('video', frame)

while(True):
    try:
        ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objPoints,imgPoints,(imgHeight,imgWidth),None,None)

        #h,w = img.shape[:2]
        newCameraMTX, roi = cv.getOptimalNewCameraMatrix(mtx,dist,(imgWidth,imgHeight),1,(imgWidth,imgHeight))

        calibrationfile = cv.FileStorage("calibrationValuesVideo.xml", cv.FILE_STORAGE_WRITE)
        calibrationfile.write("mtx", mtx)
        calibrationfile.write("dist", dist)
        calibrationfile.write("newCameraMTX",newCameraMTX)
        calibrationfile.release()
        print("Camera matrix xml file released")
    except:
        print('error in calibration attempt, likely no corners found (yet)')


cap.release()
cv.destroyAllWindows()
