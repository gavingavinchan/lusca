import cv2 as cv
import numpy as np
from glob import glob

x,y = np.meshgrid(range(7),range(6))
worldPoints = np.hstack((x.reshape(42,1),y.reshape(42,1),np.zeros((42,1)))).astype(np.float32)


objPoints = []
imgPoints =[]
numberOfphotosUsed = 0
photoprocessed = 0

imgPaths = glob('*.jpg')
for path in imgPaths:
    im = cv.imread(path,cv.COLOR_BGR2GRAY)
    print('path: ' + str(path))
    photoprocessed += 1
    print('photo processed: ' + str(photoprocessed))

    ret, corners = cv.findChessboardCorners(im, (7,6))

    if ret:
        print('good photo: ', path)
        numberOfphotosUsed += 1

        corners = corners.reshape(-1,2)

        im_vis = im.copy()
        cv.drawChessboardCorners(im_vis, (7,6), corners, ret)
        cv.imshow(str(numberOfphotosUsed), im_vis)
        imgPoints.append(corners)
        objPoints.append(worldPoints)

print(numberOfphotosUsed)

ret, mtx, dist, rvecs, tvecs = cv.calibrateCamera(objPoints,imgPoints,(im.shape[1],im.shape[0]),None,None)

cv.imshow('original',cv.imread('check.jpg'))

img = cv.imread('check.jpg',cv.IMREAD_GRAYSCALE)
h,w = img.shape[:2]
newCameraMTX, roi = cv.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))
imgUndistorted = cv.undistort(img,mtx,dist,None,newCameraMTX)
cv.imshow('undistorted', imgUndistorted)

calibrationfile = cv.FileStorage("calibrationValues.xml", cv.FILE_STORAGE_WRITE)
calibrationfile.write("mtx", mtx)
calibrationfile.write("dist", dist)
calibrationfile.write("newCameraMTX",newCameraMTX)
calibrationfile.release()
print("Camera matrix xml file released")

cv.waitKey(0)
cv.destroyAllWindows()
