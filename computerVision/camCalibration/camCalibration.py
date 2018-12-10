import numpy as np
import cv2 as cv
import glob

#termination criteria
criteria = (cv.TERM_CRITERIA_EPS + cv.TERM_CRITERIA_MAX_ITER, 25, 0.001)

#perpare objectpoints, like (0,0,0), (1,0,0)...
objp = np.zeros((6*7,3), np.float32)
objp[:,:2] = np.mgrid[0:7,0:6].T.reshape(-1,2)

#Arrays to store ohj and img points
objpoints = []
imgpoints =[]

images = glob.glob('*.jpg')


for fname in images:
    img = cv.imread(fname)
    gray = cv.cvtColor(img,cv.COLOR_BGR2GRAY)

    #find chess board corners
    ret,corners = cv.findChessboardCorners(gray,(7,6),None)

    #If found, add object/img points after being refined
    if ret == True:
        objpoints.append(objp)

        corners2 = cv.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        imgpoints.append(corners2)

        #draw and display corners
        cornerIMG = cv.drawChessboardCorners(img,(7,6),corners2,ret)

        imgHeight = img.shape[0]
        imgWidth = img.shape[1]


        resizeIMG = cv.resize(gray,(int(imgWidth*2),int(imgHeight*2)))
        cv.imshow('img',resizeIMG)

        resizeCornerIMG = cv.resize(cornerIMG,(int(imgWidth*2),int(imgHeight*2)))
        cv.imshow('determine corners',resizeCornerIMG)

        '''
        #get camera calibration matrix
        ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objpoints,imgpoints,gray.shape[::-1],None,None)

        h,w = img.shape[:2]
        newCameraMTX, roi = cv.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))

        #undistort
        undistortIMG = cv.undistort(img,mtx,dist,None,newCameraMTX)

        #crop image
        x,y,w,h = roi
        undistortIMG = undistortIMG[y:y+h, x:x+w]
        cv.imshow('undistortIMG', undistortIMG)
'''
        ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)
        h,  w = img.shape[:2]
        newcameramtx, roi=cv.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))

        # undistort
        dst = cv.undistort(img, mtx, dist, None, newcameramtx)

        #resizedst = cv.resize(dst,(int(imgWidth*2),int(imgHeight*2)))
        cv.imshow('calibresult',dst)


        cv.waitKey(0)

cv.destroyAllWindows()
