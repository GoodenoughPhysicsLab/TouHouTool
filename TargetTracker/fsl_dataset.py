import os
import cv2
import json
import shutil

from typing import Optional

_ROOT = os.path.dirname(os.path.abspath(__file__))
_THDATASET_PATH = os.path.join(_ROOT, "thdataset")

def gain_dependency() -> None:
    for thtoolroot, _, files in os.walk(os.path.join(os.path.dirname(_ROOT), "thtool")):
        for file in files:
            if file.endswith(".pyd"):
                target_path = os.path.join(_ROOT, file)
                shutil.copy2(os.path.join(thtoolroot, file), target_path)
                print("coping ", file, " -> ", target_path)
        break
    # TODO check whether copy dependency successfully

def _mkdir(path: str) -> None:
    if os.path.exists(path) and os.path.isdir(path):
        shutil.rmtree(path)
    os.makedirs(path)

def get_fsl_dataset() -> None:
    import window # c++ extension of thtool
    _mkdir(os.path.join(_THDATASET_PATH, "image"))
    _mkdir(os.path.join(_THDATASET_PATH, "label"))

    window.bind_guess()
    window.init_Gdiplus()
    try:
        game_start_status: Optional[bool] = None # False: not start, True: start, None: not checked
        counter: int = 0
        while True:
            try:
                window.save_scene_img()
                img = cv2.imread("C:/Windows/Temp/thtemp.bmp") # raise BindError if th window closed
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
                    with open(os.path.join(_THDATASET_PATH, f"label/th10-fsl_{counter // 5}.json"), "w") as f:
                        f.write(json.dumps(label, indent=2))

                    cv2.imwrite(f"{_THDATASET_PATH}/image/th10-fsl_{counter // 5}.jpg", img)

            counter += 1
    except window.BindError:
        print("Checking touhou window closed")
        return
    finally:
        window.free_Gdiplus()

if __name__ == "__main__":
    gain_dependency()
    get_fsl_dataset()