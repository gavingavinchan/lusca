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

    try:
        imgPoints.append(corners2)
        objPoints.append(worldPoints)
    except:
        print("no corners")

    retCorner, corners = cv.findCirclesGrid(blurGaussian, (4,11), flags=cv.CALIB_CB_ASYMMETRIC_GRID)

    if key & 0xFF == ord('q'):
        print('quit loop')
        break
    elif key & 0xFF == ord(' '):
        print('will take photo')
        photosTaken += 1

        if retCorner:
            numberOfFramesUsed += 1

            corners = corners.reshape(-1,2)
            corners2 = cv.cornerSubPix(blurGaussian,corners,(11,11),(-1,-1),criteria)

            frame_vis = blurGaussian.copy()
            cv.drawChessboardCorners(frame_vis, (7,6), corners2, ret)
            cv.imshow('Recognised: ' + str(numberOfFramesUsed), frame_vis)
            #imgPoints.append(corners)
            #objPoints.append(worldPoints)

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

    print("calibrateCamera done, getting optimalNewCameraMatrix")
    #h,w = img.shape[:2]
    newCameraMTX, roi = cv.getOptimalNewCameraMatrix(mtx,dist,(imgWidth,imgHeight),0,(imgWidth,imgHeight))

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
