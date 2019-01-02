import cv2 as cv
import numpy as np

resizeValue = 1


x,y = np.meshgrid(range(7),range(6))
worldPoints = np.hstack((x.reshape(42,1),y.reshape(42,1),np.zeros((42,1)))).astype(np.float32)

criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)


objPoints = []
imgPoints =[]
numberOfFramesUsed = 0

cap = cv.VideoCapture("http://192.168.0.102:8000/stream.mjpg") #or: highres.mjpg

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

        imgHeight, imgWidth, layers = frame.shape

        resizeIMG = cv.resize(frame,(int(imgWidth*resizeValue),int(imgHeight*resizeValue)))

        gray = cv.cvtColor(resizeIMG,cv.COLOR_BGR2GRAY)

        retCorner, corners = cv.findChessboardCorners(gray, (7,6))


        if retCorner:
            numberOfFramesUsed += 1

            corners = corners.reshape(-1,2)
            corners2 = cv.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)

            frame_vis = gray.copy()
            cv.drawChessboardCorners(frame_vis, (7,6), corners2, ret)
            cv.imshow('Recognised: ' + str(numberOfFramesUsed), frame_vis)
            imgPoints.append(corners2)
            objPoints.append(worldPoints)
            print("objPoints and imgPoints added.")

        else:
            cv.imshow('video', frame)

if objPoints:
    print('calibrating...')
    ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objPoints,imgPoints,(imgHeight,imgWidth),None,None)

    #h,w = img.shape[:2]
    newCameraMTX, roi = cv.getOptimalNewCameraMatrix(mtx,dist,(imgWidth,imgHeight),1,(imgWidth,imgHeight))

    calibrationfile = cv.FileStorage("calibrationValuesVideo.xml", cv.FILE_STORAGE_WRITE)
    calibrationfile.write("mtx", mtx)
    calibrationfile.write("dist", dist)
    calibrationfile.write("newCameraMTX",newCameraMTX)
    calibrationfile.release()
    print("Camera matrix xml file released")
else:
    print('no corners found (yet)')


cap.release()
cv.destroyAllWindows()
