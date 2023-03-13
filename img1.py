# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

#import cv2
from PIL import Image,ImageFilter,ImageOps

path = "Z:\Sem6\Computer Graphics\Image Processing\scenery.jpg"
'''img = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
cv2.imshow("image", img)
print(img.shape)
cv2.waitKey(0)
cv2.destroyAllWindows() '''

size = 128,128
img = Image.open(path,mode="r")
#img1 = img.filter(ImageFilter.BoxBlur(1))  #Applies BoxBlur with radius 1
#img1 = img.filter(ImageFilter.GaussianBlur(2))  #Applies Gaussian Blur filter with radius 2
#img1 = img.filter(ImageFilter.BLUR)  #Blurs the image
#img1 = img.filter(ImageFilter.MaxFilter(3))  #No idea what this does
gray_img = ImageOps.grayscale(img)  #Converts rgb image to grayscale
#img1 = img.convert('1')  #Converts rgb image to black and white
#img1 = img.filter(ImageFilter.SHARPEN)  #Sharpens the image
#img1 = img.filter(ImageFilter.SMOOTH)  #Smooths the image
img1 = gray_img.filter(ImageFilter.FIND_EDGES)
#img1 = img.resize((600,400))  #To resize the image
img1.show()
hist = gray_img.histogram()
