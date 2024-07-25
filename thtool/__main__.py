import math
import argparse
import cv2
import numpy as np
from . import prints
from . import window
from . import scene
from . import kb_control
from typing import Optional

def main() -> None:
    parser = argparse.ArgumentParser(description="thtool(TouHouTool) : tools for TouHou project")

    parser.add_argument("--version", action="store_true", help="show version")
    parser.add_argument("--bind",
                        help="bind to window."
                            "[ --bind list ] print all windows' title; "
                            "[ --bind list-guess ] print all guessed windows' title; "
                            "[ --bind foreground ] bind to foreground window; "
                            "[ --bind guess ] bind to a window thtool guessed; "
                            "[ --bind <title> ] bind to a window with title <title>")
    parser.add_argument("--always-shoot", action="store_true", help="player always shoot without pressing 'z'")
    parser.add_argument("--draw", action="store_true", help="draw the scene")

    args = parser.parse_args()

    if args.version:
        print("thtool(TouHouTool) v0.0.0")
        return

    if args.bind == "list":
        window.print_all_windows()
        return
    elif args.bind == "list-guess":
        window.print_all_windows(only_guess=True)
        return
    elif args.bind == "foreground":
        window.bind_foreground()
    elif args.bind == "guess":
        window.bind_guess()
    elif args.bind:
        window.bind_title(args.bind)
    else:
        raise window.BindError("you must bind to a TouHou window")

    if args.always_shoot:
        kb_control.send(kb_control.Behavior.shoot, deltatime=None, in_queue=True)

    game_start_status: Optional[bool] = None # False: not start, True: start, None: not checked
    window.init_Gdiplus()
    try:
        while True:
            kb_control.do_if_checkout_foreground()

            try:
                img = scene.get_scene() # raise BindError if th-window closed
                game_elements = scene.GameElements() # raise GameNotStartError if game not start
            except window.GameNotStartError:
                cv2.destroyAllWindows()
                if game_start_status is not False:
                    print("Checking touhou game NOT start")
                    game_start_status = False
            else:
                if game_start_status is not True:
                    print("Checking touhou game start")
                    game_start_status = True

                if args.draw:
                    blank = img.copy()#np.zeros_like(img)

                    # draw player
                    cv2.rectangle(
                        blank,
                        (int(game_elements.player.get_x() + 224 - game_elements.player.get_width() / 2)
                        , int(game_elements.player.get_y() + 15 - game_elements.player.get_height() / 2)),
                        (int(game_elements.player.get_x() + 224 + game_elements.player.get_width() / 2)
                        , int(game_elements.player.get_y() + 15 + game_elements.player.get_height() / 2)),
                        (255, 0, 0)
                    )

                    #draw enemies
                    for enemy in game_elements.enemies:
                        cv2.rectangle(
                            blank,
                            (int(enemy.get_x() + 224 - enemy.get_width() / 2)
                            , int(enemy.get_y() + 15 - enemy.get_height() / 2)),
                            (int(enemy.get_x() + 224 + enemy.get_width() / 2)
                            , int(enemy.get_y() + 15 + enemy.get_height() / 2)),
                            (0, 0, 255)
                        )

                    # draw enemy_bullets
                    for enemy_bullet in game_elements.enemy_bullets:
                        cv2.rectangle(
                            blank,
                            (int(enemy_bullet.get_x() + 224 - enemy_bullet.get_width() / 2)
                            , int(enemy_bullet.get_y() + 15 - enemy_bullet.get_height() / 2)),
                            (int(enemy_bullet.get_x() + 224 + enemy_bullet.get_width() / 2)
                            , int(enemy_bullet.get_y() + 15 + enemy_bullet.get_height() / 2)),
                            (0, 0, 255)
                        )

                    # draw enemy_lasers
                    def _rotate_point(cx, cy, x, y, radian):
                        res_x = cx + (x - cx) * math.cos(radian) - (y - cy) * math.sin(radian)
                        res_y = cy + (x - cx) * math.sin(radian) + (y - cy) * math.cos(radian)
                        return res_x, res_y

                    for enemy_laser in game_elements.enemy_lasers:
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

                        pts = np.array([
                            [224 + _x1, 15 + _y1],
                            [224 + _x2, 15 + _y2],
                            [224 + _x3, 15 + _y3],
                            [224 + _x4, 15 + _y4],
                        ], dtype=np.int32)
                        cv2.polylines(blank, [pts], True, (0, 0, 255))

                    # draw resources
                    for resource in game_elements.resources:
                        cv2.rectangle(
                            blank,
                            (int(resource.get_x() + 224 - resource.get_width() / 2)
                            , int(resource.get_y() + 15 - resource.get_height() / 2)),
                            (int(resource.get_x() + 224 + resource.get_width() / 2)
                            , int(resource.get_y() + 15 + resource.get_height() / 2)),
                            (0, 255, 0)
                        )

                    cv2.imshow("thtool", blank)
                    cv2.waitKey(1)
    except window.BindError:
        print("Checking touhou window closed")
        exit(0)
    finally:
        kb_control.release_all()
        cv2.destroyAllWindows()
        window.free_Gdiplus()


if __name__ == '__main__':
    try:
        prints.enable_win32_ansi()
        main()
    except KeyboardInterrupt:
        print("Keyboard interrupt!")
else:
    raise RuntimeError("This file is not intended to be imported!")
