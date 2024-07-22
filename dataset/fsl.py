import os
import cv2
import json
from . import window
from . import scene

def get_fsl_dataset():
    ROOT = os.path.dirname(os.path.abspath(__file__))
    thdataset_path = os.path.join(ROOT, "thdataset")
    if not os.path.exists(thdataset_path) and not os.path.isdir(thdataset_path):
        os.mkdir(thdataset_path)

    window.bind_guess()

    window.init_Gdiplus()
    try:
        counter: int = 0
        while True:
            try:
                img = scene.get_scene() # raise BindError if th window closed
                label = {
                    "player": window.fsl_get_player(), # raise GameNotStartError if th-game not started
                    "enemies": window.fsl_get_enemies(),
                    "enemy_bullets": window.fsl_get_enemy_bullets(), # can dx, dy be guessed by ai?
                    "resources": window.fsl_get_resources(),
                }

            except window.GameNotStartError:
                print("Checking touhou game NOT start", end="\r")
            else:
                print("Checking touhou game start    ", end="\r")

                with open(os.path.join(thdataset_path, f"label/th10-fsl_{counter // 25}.json"), "w") as f:
                    f.write(json.dumps(label, indent=2))

                if counter % 25 == 0:
                    cv2.imwrite(f"{thdataset_path}/image/th10-fsl_{counter // 25}.jpg", img)

            counter += 1
    except window.BindError:
        print("\nChecking touhou window closed")
        exit(0)
    finally:
        window.free_Gdiplus()
