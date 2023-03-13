# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import cv2
import matplotlib.pyplot as plt
import numpy as np

img = cv2.imread("C:\\Users\\pl\\Downloads\\Panda.jpg",0)

#Plot histogram

plt.subplot(1,2,1)
plt.imshow(img,cmap='gray')
plt.title('image')
plt.xticks([])
plt.yticks([])

plt.subplot(1,2,2)
hist,bin = np.histogram(img.ravel(),256,[0,255])
plt.xlim([0,255])
plt.plot(hist)
plt.title('histogram')
plt.show()

#Perform erosion and dilation
kernel = np.ones((5,5),np.uint8())
img_erosion = cv2.erode(img,kernel,iterations = 2)
img_dilation = cv2.dilate(img,kernel,iterations = 2)

'''cv2.imshow('Input Image', img)
#cv2.imshow('Erosion',img_erosion)
cv2.imshow('Dilation',img_dilation)
cv2.waitKey(0)'''

plt.subplot(1,3,1)
plt.imshow(img,cmap = 'gray')
plt.title('Original Image')
plt.xticks([])
plt.yticks([])

plt.subplot(1,3,2)
plt.imshow(img_erosion,cmap = 'gray')
plt.title('Erosion')
plt.xticks([])
plt.yticks([])

plt.subplot(1,3,3)
plt.imshow(img_dilation,cmap = 'gray')
plt.title('Dilation')
plt.xticks([])
plt.yticks([])

plt.show()


#Perform canny edge detection
edges = cv2.Canny(img,75,75)
plt.imshow(edges,cmap = 'gray')
plt.xticks([])
plt.yticks([])
plt.show()