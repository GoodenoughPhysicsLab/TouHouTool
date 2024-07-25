import os
import json
import shutil
from fsl_dataset import _mkdir, _THDATASET_PATH

def _label_to_yolotxt(label: dict) -> str:
    res = ""

    #player
    player_x, player_y = label["player"]
    res += f"0 {(player_x - 2) / 640} {(player_y - 2) / 480}" \
            f" {(player_x + 2) / 640} {(player_y - 2) / 480}" \
            f" {(player_x + 2) / 640} {(player_y + 2) / 480}" \
            f" {(player_x - 2) / 640} {(player_y + 2) / 480}\n"

    # enemy
    for enemy_x, enemy_y, enemy_width, enemy_height in label["enemies"]:
        if enemy_y < 0:
            continue
        res += f"1 {(enemy_x - enemy_width / 2) / 640} {(enemy_y - enemy_height / 2) / 480}" \
                f" {(enemy_x + enemy_width / 2) / 640} {(enemy_y - enemy_height / 2) / 480}" \
                f" {(enemy_x + enemy_width / 2) / 640} {(enemy_y + enemy_height / 2) / 480}" \
                f" {(enemy_x - enemy_width / 2) / 640} {(enemy_y + enemy_height / 2) / 480}\n"

    # enemy_bullet
    return res

def generate_yolo() -> None:
    _mkdir(os.path.join(_THDATASET_PATH, "yolo", "image", "train"))
    _mkdir(os.path.join(_THDATASET_PATH, "yolo", "image", "valid"))
    _mkdir(os.path.join(_THDATASET_PATH, "yolo", "image", "test"))
    _mkdir(os.path.join(_THDATASET_PATH, "yolo", "label", "train"))
    _mkdir(os.path.join(_THDATASET_PATH, "yolo", "label", "valid"))
    _mkdir(os.path.join(_THDATASET_PATH, "yolo", "label", "test"))

    with open(os.path.join(_THDATASET_PATH, "yolo/thdataset.yaml"), 'w') as f:
        f.write(f"train: {_THDATASET_PATH}\\yolo\\image\\train\n"
                f"val: {_THDATASET_PATH}\\yolo\\image\\valid\n"
                f"test: {_THDATASET_PATH}\\yolo\\image\\test\n"
                f"nc: 5\n"
                f"names: ['player', 'enemy', 'enemy_bullet', 'enemy_laser', 'resources']")

    for imageroot, _, files in os.walk(os.path.join(_THDATASET_PATH, "image")):
        train_amount = int(len(files) * 0.7)
        for i, file in enumerate(files):
            if i < train_amount:
                shutil.copy(os.path.join(imageroot, file),
                            os.path.join(_THDATASET_PATH, "yolo/image/train", file))
            else:
                shutil.copy(os.path.join(imageroot, file),
                            os.path.join(_THDATASET_PATH, "yolo/image/valid", file))
        break
    for labelroot, _, files in os.walk(os.path.join(_THDATASET_PATH, "label")):
        train_amount = int(len(files) * 0.7)
        for i, file in enumerate(files):
            with open(os.path.join(labelroot, file)) as f:
                context = json.load(f)

            if i < train_amount:
                with open(os.path.join(_THDATASET_PATH, "yolo/label/train",
                                       file.replace(".json", ".txt")), 'w') as f:
                    f.write(_label_to_yolotxt(context))
            else:
                with open(os.path.join(_THDATASET_PATH, "yolo/label/valid",
                                       file.replace(".json", ".txt")), 'w') as f:
                    f.write(_label_to_yolotxt(context))
        break