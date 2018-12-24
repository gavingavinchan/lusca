import cv2
import numpy

def crop_center(img,cropx,cropy):
    y,x = img.shape
    startx = x//2-(cropx//2)
    starty = y//2-(cropy//2)
    return img[starty:starty+cropy,startx:startx+cropx]

img = cv2.imread("checkerboardIMG.jpg")

crop_img = img[20:30, 20:30]
cv2.imshow("cropped", crop_img)
cv2.waitKey(0)
