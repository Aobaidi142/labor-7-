import RPi.GPIO as GPIO
import time
import cv2
import numpy as np

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(24, GPIO.OUT) #Pin 19, GPIO 18
GPIO.setup(23, GPIO.OUT)

cap = cv2.VideoCapture(0)
currentcolor = "No Color"
 
    
def checkcolor()  : 
    
    #Take each frame
    _, frame = cap.read()
    
    #Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    #define range of blue color in HSV
    #lower_blue = np.array([110, 50, 50])
    #upper_blue = np.array([130, 255, 255])
    
    lower_blue = np.array([110, 100, 100])
    upper_blue = np.array([130, 255, 255])
    
    #Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    
    #Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame, frame, mask = mask)
    
    counter = np.sum(res != [0, 0, 0])
   
    
    if (counter > 9000):
        currentcolor = "Blue"
        GPIO.output(23, GPIO.HIGH)
        time.sleep(1)
        GPIO.output(23, GPIO.LOW)
        currentcolor = "No Color"
  
         
   
        
        
    lower_red = np.array([160, 100, 100])
    upper_red = np.array([190, 255, 255])
    
    #Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower_red, upper_red)
    
    #Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame, frame, mask = mask)
    
    counter = np.sum(res != [0, 0, 0])
    if (counter > 9000):
        currentcolor = "Red" 
        GPIO.output(23, GPIO.HIGH)
        time.sleep(1)
        GPIO.output(23, GPIO.LOW)
        currentcolor = "No Color"
        

    
       
        
    
    
    return currentcolor 
    
    while (1):
        print(checkcolor())
        cv2.imshow('frame', frame)
        cv2.imshow('mask', mask)
        cv2.imshow('res',res)
        k = cv2.waitKey(5) & 0xF
        if k == 27:
            break;
         
    
    
cv2.destroyAllWindows()
