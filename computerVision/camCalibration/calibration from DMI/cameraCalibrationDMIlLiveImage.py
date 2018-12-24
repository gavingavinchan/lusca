import cv2 as cv
import numpy as np

resizeValue = 1


x,y = np.meshgrid(range(7),range(6))
worldPoints = np.hstack((x.reshape(42,1),y.reshape(42,1),np.zeros((42,1)))).astype(np.float32)


objPoints = []
imgPoints =[]
numberOfFramesUsed = 0

cap = cv.VideoCapture(0)

imgWidth = 0
imgHeight = 0

key = -1
photosTaken = 0
while(True):
    ret, frame = cap.read()

    imgHeight, imgWidth, layers = frame.shape

    resizeIMG = cv.resize(frame,(int(imgWidth*resizeValue),int(imgHeight*resizeValue)))

    retCorner, corners = cv.findChessboardCorners(resizeIMG, (7,6))

    if key & 0xFF == ord('q'):
        print('quit loop')
        break
    elif key & 0xFF == ord(' '):
        print('will take photo')
        photosTaken += 1

        if retCorner:
            numberOfFramesUsed += 1

            corners = corners.reshape(-1,2)

            frame_vis = frame.copy()
            cv.drawChessboardCorners(frame_vis, (7,6), corners, ret)
            cv.imshow(str(numberOfFramesUsed), frame_vis)
            imgPoints.append(corners)
            objPoints.append(worldPoints)

        else:
            h = 100
            w = 100
            cropIMG = frame[y:y+h, x:x+w].copy()
            cv.imshow(str(photosTaken), cropIMG)

    else:
        cv.imshow('preview', frame)

    key = cv.waitKey(1)



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
