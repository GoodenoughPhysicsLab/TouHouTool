import os
import cv2
import json
from . import window
from . import scene
from typing import Optional

def get_fsl_dataset():
    ROOT = os.path.dirname(os.path.abspath(__file__))
    thdataset_path = os.path.join(ROOT, "thdataset")
    if not os.path.exists(thdataset_path) and not os.path.isdir(thdataset_path):
        os.mkdir(thdataset_path)
    if not os.path.exists(os.path.join(thdataset_path, "image")):
        os.mkdir(os.path.join(thdataset_path, "image"))
    if not os.path.exists(os.path.join(thdataset_path, "label")):
        os.mkdir(os.path.join(thdataset_path, "label"))

    window.bind_guess()

    window.init_Gdiplus()
    try:
        game_start_status: Optional[bool] = None # False: not start, True: start, None: not checked
        counter: int = 0
        while True:
            try:
                img = scene.get_scene() # raise BindError if th window closed
                label = {
                    "player": window.fsl_get_player(), # raise GameNotStartError if th-game not started
                    "enemies": window.fsl_get_enemies(),
                    # bullets' dx, dy can't be guessed by ai
                    "enemy_bullets": [bullet[:4] for bullet in window.fsl_get_enemy_bullets()],
                    "enemy_laser": window.fsl_get_enemy_lasers(),
                    "resources": window.fsl_get_resources(),
                }

            except window.GameNotStartError:
                if game_start_status is not False:
                    print("Checking touhou game NOT start")
                    game_start_status = False
            else:
                if game_start_status is not True:
                    print("Checking touhou game start")
                    game_start_status = True

                if counter % 5 == 0:
                    with open(os.path.join(thdataset_path, f"label/th10-fsl_{counter // 5}.json"), "w") as f:
                        f.write(json.dumps(label, indent=2))

                    cv2.imwrite(f"{thdataset_path}/image/th10-fsl_{counter // 5}.jpg", img)

            counter += 1
    except window.BindError:
        print("Checking touhou window closed")
        exit(0)
    finally:
        window.free_Gdiplus()
