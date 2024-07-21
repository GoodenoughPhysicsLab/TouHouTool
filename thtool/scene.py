import cv2
import numpy as np
from . import window
from . import obj
from typing import List

def get_scene() -> np.ndarray:
    window.save_scene_img()
    return cv2.imread("C:/Windows/Temp/thtemp.bmp")

def get_player() -> obj.Player:
    return obj.Player(*window.fsl_get_player())

def get_resources() -> List[obj.Resource]:
    return [obj.Resource(*resource) for resource in window.fsl_get_resources()]