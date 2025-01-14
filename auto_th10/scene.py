import math
import cv2
import numpy as np
from . import objects
from . import window
from typing import List, Tuple

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

# Note:
#   the position window module readed is NOT the screen position
#   this file will transform them to screen position

def get_player() -> objects.Player:
    if window.get_th_game() == window.ThGame.fsl:
        x, y = window.fsl_get_player()
        return objects.Player(x + 224, y + 15)
    pass
    raise RuntimeError("don't support in this version")

def get_player_point() -> Tuple[Tuple[int, int], Tuple[int, int]]:
    player = get_player()
    if window.get_th_game() == window.ThGame.fsl:
        return ((int(player.get_x() - player.get_width() / 2)
                , int(player.get_y() - player.get_height() / 2)),
                (int(player.get_x() + player.get_width() / 2)
                , int(player.get_y() + player.get_height() / 2)))
    pass
    raise RuntimeError("don't support in this version")

def get_enemies() -> List[objects.Enemy]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for x, y, width, height in window.fsl_get_enemies():
            res.append(objects.Enemy(x + 224, y + 15, width, height))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_points() -> List[Tuple[Tuple[int, int], Tuple[int, int]]]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for enemy in get_enemies():
            res.append(((int(enemy.get_x() - enemy.get_width() / 2)
                        , int(enemy.get_y() - enemy.get_height() / 2)),
                        (int(enemy.get_x() + enemy.get_width() / 2)
                        , int(enemy.get_y() + enemy.get_height() / 2))))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_bullets() -> List[objects.EnemyBullet]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for x, y, width, height, dx, dy in window.fsl_get_enemy_bullets():
            res.append(objects.EnemyBullet(x + 224, y + 15, width, height, dx, dy))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_bullet_points() -> List[Tuple[Tuple[int, int], Tuple[int, int]]]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for enemy_bullet in get_enemy_bullets():
            res.append(((int(enemy_bullet.get_x() - enemy_bullet.get_width() / 2)
                        , int(enemy_bullet.get_y() - enemy_bullet.get_height() / 2)),
                        (int(enemy_bullet.get_x() + enemy_bullet.get_width() / 2)
                        , int(enemy_bullet.get_y() + enemy_bullet.get_height() / 2))))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_lasers() -> List[objects.EnemyLaser]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for x, y, width, height, arc in window.fsl_get_enemy_lasers():
            res.append(objects.EnemyLaser(x + 224, y + 15, width, height, arc))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_enemy_laser_points() \
        -> List[Tuple[Tuple[int, int], Tuple[int, int], Tuple[int, int], Tuple[int, int]]]:
    def _rotate_point(x_center, y_center, x, y, radian):
        res_x = x_center + (x - x_center) * math.cos(radian) - (y - y_center) * math.sin(radian)
        res_y = y_center + (x - x_center) * math.sin(radian) + (y - y_center) * math.cos(radian)
        return res_x, res_y

    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for enemy_laser in get_enemy_lasers():
            _x1, _y1 = _rotate_point(
                enemy_laser.get_x(), enemy_laser.get_y(),
                enemy_laser.get_x() - enemy_laser.get_width() / 2,
                enemy_laser.get_y(),
                enemy_laser.get_radian() - math.pi / 2
            )
            _x2, _y2 = _rotate_point(
                enemy_laser.get_x(), enemy_laser.get_y(),
                enemy_laser.get_x() + enemy_laser.get_width() / 2,
                enemy_laser.get_y(),
                enemy_laser.get_radian() - math.pi / 2
            )
            _x3, _y3 = _rotate_point(
                enemy_laser.get_x(), enemy_laser.get_y(),
                enemy_laser.get_x() + enemy_laser.get_width() / 2,
                enemy_laser.get_y() + enemy_laser.get_height(),
                enemy_laser.get_radian() - math.pi / 2
            )
            _x4, _y4 = _rotate_point(
                enemy_laser.get_x(), enemy_laser.get_y(),
                enemy_laser.get_x() - enemy_laser.get_width() / 2,
                enemy_laser.get_y() + enemy_laser.get_height(),
                enemy_laser.get_radian() - math.pi / 2
            )

            res.append(((_x1, _y1), (_x2, _y2), (_x3, _y3), (_x4, _y4)))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_resources() -> List[objects.Resource]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for x, y in window.fsl_get_resources():
            res.append(objects.Resource(x + 224, y + 15))
        return res
    pass
    raise RuntimeError("don't support in this version")

def get_resource_points() -> List[Tuple[Tuple[int, int], Tuple[int, int]]]:
    if window.get_th_game() == window.ThGame.fsl:
        res: list = []
        for resource in get_resources():
            res.append(((int(resource.get_x() - resource.get_width() / 2)
                        , int(resource.get_y() - resource.get_height() / 2)),
                        (int(resource.get_x() + resource.get_width() / 2)
                        , int(resource.get_y() + resource.get_height() / 2))))
        return res
    pass
    raise RuntimeError("don't support in this version")
