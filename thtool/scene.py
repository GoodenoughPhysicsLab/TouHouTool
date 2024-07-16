import cv2
from . import window

def get_scene():
    window.save_scene_img()
    return cv2.imread("C:/Windows/Temp/thtemp.bmp")