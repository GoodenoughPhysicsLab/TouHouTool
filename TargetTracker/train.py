import os
import json
import math
import shutil
from fsl_dataset import _mkdir, _THDATASET_PATH, _ROOT

def _rotate_point(x_center, y_center, x, y, radian):
    res_x = x_center + (x - x_center) * math.cos(radian) - (y - y_center) * math.sin(radian)
    res_y = y_center + (x - x_center) * math.sin(radian) + (y - y_center) * math.cos(radian)
    return res_x, res_y

def _data_fmt(num: float) -> float:
    return min(1, max(0, num))

def _label_to_yolotxt(label: dict) -> str:
    res = ""

    #player
    player_x, player_y = label["player"]
    if 0 < player_y + 17 < 480:
        res += f"0 {(player_x + 224 - 2) / 640} {(player_y + 15 - 2) / 480}" \
                f" {(player_x + 224 + 2) / 640} {(player_y + 15 - 2) / 480}" \
                f" {(player_x + 224 + 2) / 640} {(player_y + 15 + 2) / 480}" \
                f" {(player_x + 224 - 2) / 640} {(player_y + 15 + 2) / 480}\n"

    # enemy
    enemy_set = set()
    for enemy_x, enemy_y, enemy_width, enemy_height in label["enemies"]:
        if enemy_y < 0:
            continue
        enemy_set.add((
            _data_fmt((enemy_x + 224 - enemy_width / 2) / 640),
            _data_fmt((enemy_y + 15 - enemy_height / 2) / 480),
            _data_fmt((enemy_x + 224 + enemy_width / 2) / 640),
            _data_fmt((enemy_y + 15 - enemy_height / 2) / 480),
            _data_fmt(enemy_x + 224 + enemy_width / 2) / 640,
            _data_fmt((enemy_y + 15 + enemy_height / 2) / 480),
            _data_fmt(enemy_x + 224 - enemy_width / 2) / 640,
            _data_fmt((enemy_y + 15 + enemy_height / 2) / 480),
        ))
    for x1, y1, x2, y2, x3, y3, x4, y4 in enemy_set:
        res += f"1 {x1} {y1} {x2} {y2} {x3} {y3} {x4} {y4}\n"

    # enemy_bullet
    enemy_bullet_set = set()
    for enemy_bullet_x, enemy_bullet_y, enemy_bullet_width, enemy_bullet_height in label["enemy_bullets"]:
        if enemy_bullet_y < 0:
            continue
        enemy_bullet_set.add((
            _data_fmt((enemy_bullet_x + 224 - enemy_bullet_width / 2) / 640),
            _data_fmt((enemy_bullet_y + 15 - enemy_bullet_height / 2) / 480),
            _data_fmt((enemy_bullet_x + 224 + enemy_bullet_width / 2) / 640),
            _data_fmt((enemy_bullet_y + 15 - enemy_bullet_height / 2) / 480),
            _data_fmt((enemy_bullet_x + 224 + enemy_bullet_width / 2) / 640),
            _data_fmt((enemy_bullet_y + 15 + enemy_bullet_height / 2) / 480),
            _data_fmt((enemy_bullet_x + 224 - enemy_bullet_width / 2) / 640),
            _data_fmt((enemy_bullet_y + 15 + enemy_bullet_height / 2) / 480),
        ))
    for x1, y1, x2, y2, x3, y3, x4, y4 in enemy_bullet_set:
        res += f"2 {x1} {y1} {x2} {y2} {x3} {y3} {x4} {y4}\n"

    # enemy_laser
    enemy_laser_set = set()
    for enemy_laser_x, enemy_laser_y, enemy_laser_width, enemy_laser_height, radian in label["enemy_laser"]:
        _x1, _y1 = _rotate_point(
            enemy_laser_x, enemy_laser_y,
            enemy_laser_x - enemy_laser_width / 2,
            enemy_laser_y,
            radian - math.pi / 2
        )
        _x2, _y2 = _rotate_point(
            enemy_laser_x, enemy_laser_y,
            enemy_laser_x + enemy_laser_width / 2,
            enemy_laser_y,
            radian - math.pi / 2
        )
        _x3, _y3 = _rotate_point(
            enemy_laser_x, enemy_laser_y,
            enemy_laser_x + enemy_laser_width / 2,
            enemy_laser_y + enemy_laser_height,
            radian - math.pi / 2
        )
        _x4, _y4 = _rotate_point(
            enemy_laser_x, enemy_laser_y,
            enemy_laser_x - enemy_laser_width / 2,
            enemy_laser_y + enemy_laser_height,
            radian - math.pi / 2
        )
        enemy_bullet_set.add((
            _data_fmt((_x1 + 224) / 640), _data_fmt((_y1 + 15) / 480),
            _data_fmt((_x2 + 224) / 640), _data_fmt((_y2 + 15) / 480),
            _data_fmt((_x3 + 224) / 640), _data_fmt((_y3 + 15) / 480),
            _data_fmt((_x4 + 224) / 640), _data_fmt((_y4 + 15) / 480),
        ))
    for x1, y1, x2, y2, x3, y3, x4, y4 in enemy_laser_set:
        res += f"3 {x1} {y1} {x2} {y2} {x3} {y3} {x4} {y4}\n"

    # resources
    resource_set = set()
    for resource_x, resource_y in label["resources"]:
        if resource_y < 0:
            continue
        resource_set.add((
            _data_fmt((resource_x + 224 - 3) / 640), _data_fmt((resource_y + 15 - 3) / 480),
            _data_fmt((resource_x + 224 + 3) / 640), _data_fmt((resource_y + 15 - 3) / 480),
            _data_fmt((resource_x + 224 + 3) / 640), _data_fmt((resource_y + 15 + 3) / 480),
            _data_fmt((resource_x + 224 - 3) / 640), _data_fmt((resource_y + 15 + 3) / 480)
        ))
    for x1, y1, x2, y2, x3, y3, x4, y4 in resource_set:
        res += f"4 {x1} {y1} {x2} {y2} {x3} {y3} {x4} {y4}\n"

    return res

def generate_yolo() -> None:
    train_images = os.path.join(_THDATASET_PATH, "yolo", "train", "images")
    train_labels = os.path.join(_THDATASET_PATH, "yolo", "train", "labels")
    val_images = os.path.join(_THDATASET_PATH, "yolo", "val", "images")
    val_labels = os.path.join(_THDATASET_PATH, "yolo", "val", "labels")
    test_images = os.path.join(_THDATASET_PATH, "yolo", "test", "images")
    test_labels = os.path.join(_THDATASET_PATH, "yolo", "test", "labels")
    _mkdir(train_images)
    _mkdir(train_labels)
    _mkdir(val_images)
    _mkdir(val_labels)
    _mkdir(test_images)
    _mkdir(test_labels)

    with open(os.path.join(_THDATASET_PATH, "yolo", "thdataset.yaml"), 'w') as f:
        f.write(f"train: {train_images}\n"
                f"val: {val_images}\n"
                f"test: {test_images}\n"
                f"nc: 5\n"
                f"names: ['player', 'enemy', 'enemy_bullet', 'enemy_laser', 'resources']")

    print("tackle image")
    for imageroot, _, files in os.walk(os.path.join(_THDATASET_PATH, "image")):
        train_amount = int(len(files) * 0.7)
        for i, file in enumerate(files):
            if i < train_amount:
                shutil.copy(os.path.join(imageroot, file),
                            os.path.join(train_images, file))
            else:
                shutil.copy(os.path.join(imageroot, file),
                            os.path.join(val_images, file))
        break
    print("tackle label")
    for labelroot, _, files in os.walk(os.path.join(_THDATASET_PATH, "label")):
        train_amount = int(len(files) * 0.7)
        for i, file in enumerate(files):
            with open(os.path.join(labelroot, file)) as f:
                context = json.load(f)

            if i < train_amount:
                with open(os.path.join(train_labels, file.replace(".json", ".txt")), 'w') as f:
                    f.write(_label_to_yolotxt(context))
            else:
                with open(os.path.join(val_labels, file.replace(".json", ".txt")), 'w') as f:
                    f.write(_label_to_yolotxt(context))
        break

def train(valid: bool = False) -> None:
    from ultralytics import YOLO
    if not os.path.exists("runs"):
        model = YOLO("yolov8m-obb.pt")
    else:
        fold_count = len(list(os.walk(os.path.join("runs", "obb")))[0][1])
        if fold_count == 1:
            fold_count = ""
        model = YOLO(os.path.join(
            os.path.dirname(_ROOT), "runs", "obb", f"train{fold_count}", "weights", "best.pt")
        )
    model.train(data=os.path.join(_THDATASET_PATH, "yolo", "thdataset.yaml"), epochs=16, imgsz=640, batch=2)
    if valid:
        model.val()

if __name__ == "__main__":
    if not os.path.exists(os.path.join(_THDATASET_PATH, "yolo")):
        generate_yolo()
    print("train START")
    train()
    print("train END")
