import cv2 as cv
import numpy as np

cvFile = cv.FileStorage("calibrationValuesVideo.xml",cv.FILE_STORAGE_READ)
mtx = cvFile.getNode("mtx").mat()
dist = cvFile.getNode("dist").mat()
newCameraMTX = cvFile.getNode("newCameraMTX").mat()

img = cv.imread("check.jpg")
cv.imshow("original",img)
imgUndistorted = cv.undistort(img,mtx,dist,None,newCameraMTX)
cv.imshow("undistorted", imgUndistorted)


cv.waitKey(0)
cv.destroyAllWindows()
