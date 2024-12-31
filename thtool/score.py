import pytesseract
import cv2
import numpy as np
from . import window

def get_score_img(src_scene: np.ndarray) -> np.ndarray:
    _, res = cv2.threshold(src_scene[70:100, 500:], 128, 255, cv2.THRESH_BINARY)
    return res

def get_score() -> int:
    if window.get_th_game() == window.ThGame.fsl:
        return window.fsl_get_score() * 10
    pass

def get_score_generally(src_scene: np.ndarray) -> int:
    return int(pytesseract.image_to_string((get_score_img(src_scene)), config="--oem 3 --psm 6 outputbase digits"))
