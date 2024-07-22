import cv2
import numpy as np
from . import obj
from . import window
from typing import List

def get_scene() -> np.ndarray:
    window.save_scene_img()
    return cv2.imread("C:/Windows/Temp/thtemp.bmp")

def get_player() -> obj.Player:
    return obj.Player(*window.fsl_get_player())

def get_enemies() -> List[obj.Enemy]:
    return [obj.Enemy(*enemy) for enemy in window.fsl_get_enemies()]

def get_enemy_bullets() -> List[obj.EnemyBullet]:
    return [obj.EnemyBullet(*bullet) for bullet in window.fsl_get_enemy_bullets()]

def get_resources() -> List[obj.Resource]:
    return [obj.Resource(*resource) for resource in window.fsl_get_resources()]
