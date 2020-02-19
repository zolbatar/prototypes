# import the necessary packages
import imutils
import numpy as np
import argparse
import cv2
import os

# define the upper and lower boundaries of the HSV pixel
# intensities to be considered 'skin'
lower = np.array([0, 48, 80], dtype = "uint8")
upper = np.array([20, 255, 255], dtype = "uint8")

for file in os.listdir("O:/Download"):
    print(file)
    image = cv2.imread("O:/Download/" + file)

    converted = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    skinMask = cv2.inRange(converted, lower, upper)

    v = cv2.countNonZero(skinMask)
    if (v < 150000 or v > 400000):
        os.rename("O:/Download/" + file, "O:/Download/No/" + file)

#    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (11, 11))
#    updatedMask = cv2.erode(skinMask, kernel, iterations = 2)
#    updatedMask = cv2.dilate(skinMask, kernel, iterations = 2)
	
#    cv2.imshow("original", image)
#    cv2.imshow("updated", skinMask)
#    print(cv2.countNonZero(skinMask))
#    cv2.waitKey(0)
