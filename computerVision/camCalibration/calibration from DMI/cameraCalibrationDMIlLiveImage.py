import cv2 as cv
import numpy as np
import glob

resizeValue = 1


x,y = np.meshgrid(range(7),range(6))
worldPoints = np.hstack((x.reshape(42,1),y.reshape(42,1),np.zeros((42,1)))).astype(np.float32)


criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 30, 0.001)

objPoints = []
imgPoints =[]
numberOfFramesUsed = 0

cap = cv.VideoCapture("http://192.168.0.102:8000/stream.mjpg") #or: highres.mjpg
#cap = cv.VideoCapture(0)

imgWidth = 0
imgHeight = 0

key = -1
photosTaken = 0
while(True):
    ret, frame = cap.read()

    imgHeight, imgWidth, layers = frame.shape

    resizeIMG = cv.resize(frame,(int(imgWidth*resizeValue),int(imgHeight*resizeValue)))

    gray = cv.cvtColor(resizeIMG,cv.COLOR_BGR2GRAY)

    blurGaussian = cv.GaussianBlur(gray, (5,5),0)



    retCorner, corners = cv.findChessboardCorners(blurGaussian, (7,6))

    if key & 0xFF == ord('q'):
        print('quit loop')
        break
    elif key& 0xFF == ord('r'):         #delete frame with badly detected chessboard corners
        try:
            del imgPoints[-1]
            del objPoints[-1]
        except:
            print('no more imgPoints & objPoints to delete')
        cv.destroyWindow('Recognised: ' + str(numberOfFramesUsed))
        if numberOfFramesUsed > 0:
            numberOfFramesUsed -= 1
    elif key & 0xFF == ord(' '):
        print('will take photo')
        photosTaken += 1

        if retCorner:
            numberOfFramesUsed += 1

            corners = corners.reshape(-1,2)
            corners2 = cv.cornerSubPix(blurGaussian,corners,(11,11),(-1,-1),criteria)

            frame_vis = blurGaussian.copy()
            cv.drawChessboardCorners(frame_vis, (7,6), corners2, ret)
            #cv.drawChessboardCorners(frame_vis, (7,6), corners, ret)
            cv.imshow('Recognised: ' + str(numberOfFramesUsed), frame_vis)
            imgPoints.append(corners2)
            objPoints.append(worldPoints)
            print("objPoints and imgPoints added.")

        else:
            '''
            h = 100
            w = 100
            cropIMG = frame[y:y+h, x:x+w].copy()
            cv.imshow(str(photosTaken), cropIMG)
            '''
            cv.imshow(str(photosTaken), blurGaussian)

        print("photosTaken: ", photosTaken, "Recognised: ", numberOfFramesUsed)

    else:
        cv.imshow('preview', frame)

    key = cv.waitKey(1)



if objPoints:
    print('calibrating...')
    ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objPoints,imgPoints,blurGaussian.shape[::-1],None,None)

    totalError = 0
    totalPoints = 0
    for i in range(len(objPoints)):
        imgPoints2, _ = cv.projectPoints(objPoints[i],rvecs[i],tvecs[i],mtx,dist)
        imgPoints2 = imgPoints2.reshape(-1,2)
        totalError += np.sum(np.abs(imgPoints[i]-imgPoints2)**2)
        totalPoints += len(objPoints[i])
        print("mean error", totalError/totalPoints)

    print("calibrateCamera done, getting optimalNewCameraMatrix")
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
