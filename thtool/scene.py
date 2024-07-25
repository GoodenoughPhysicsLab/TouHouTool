import cv2
import numpy as np
from . import obj
from . import window
from typing import List

class GameElements:
    def __init__(self):
        self.player = get_player()
        self.enemies = get_enemies()
        self.enemy_bullets = get_enemy_bullets()
        self.enemy_lasers = get_enemy_lasers()
        self.resources = get_resources()

    def to_dict(self) -> dict:
        return {
            "player": self.player,
            "enemies": self.enemies,
            "enemy_bullets": self.enemy_bullets,
            "resources": self.resources,
        }

def get_scene() -> np.ndarray:
    window.save_scene_img()
    return cv2.imread("C:/Windows/Temp/thtemp.bmp")

def get_player() -> obj.Player:
    if window.get_th_game() == window.ThGame.fsl:
        return obj.Player(*window.fsl_get_player())
    pass
    raise RuntimeError("don't support in this version")

def get_enemies() -> List[obj.Enemy]:
    if window.get_th_game() == window.ThGame.fsl:
        return [obj.Enemy(*enemy) for enemy in window.fsl_get_enemies()]
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_bullets() -> List[obj.EnemyBullet]:
    if window.get_th_game() == window.ThGame.fsl:
        return [obj.EnemyBullet(*bullet) for bullet in window.fsl_get_enemy_bullets()]
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_lasers() -> List[obj.EnemyLaser]:
    if window.get_th_game() == window.ThGame.fsl:
        return [obj.EnemyLaser(*laser) for laser in window.fsl_get_enemy_lasers()]
    pass
    raise RuntimeError("don't support in this version")

def get_resources() -> List[obj.Resource]:
    if window.get_th_game() == window.ThGame.fsl:
        return [obj.Resource(*resource) for resource in window.fsl_get_resources()]
    pass
    raise RuntimeError("don't support in this version")
