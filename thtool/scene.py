import cv2
import numpy as np
from . import window
from . import obj

def get_scene() -> np.ndarray:
    window.save_scene_img()
    return cv2.imread("C:/Windows/Temp/thtemp.bmp")

def get_player():
    return obj.Player(*window.fsl_get_player())
