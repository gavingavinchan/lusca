import cv2 as cv
from matplotlib import pyplot as plt


img_left = cv.imread('left01.jpg')
img_right = cv.imread('right01.jpg')


#for show Corners for one image only

plt.subplot(121)
plt.imshow(img_left[...,::-1])
plt.subplot(122)
plt.imshow(img_right[...,::-1])
plt.show()


ret, corners = cv.findChessboardCorners(img_left, (7,6))
corners = corners.reshape(-1,2)

img_left_vis = img_left.copy()
cv. drawChessboardCorners(img_left_vis, (7,6), corners, ret)
plt.imshow(img_left_vis)
plt.show()
