''' please run make.py before this file
'''
import os
import shutil

if __name__ == "__main__":
    ROOT = os.path.dirname(os.path.abspath(__file__))
    for thtoolroot, _, files in os.walk(os.path.join(os.path.dirname(ROOT), "thtool")):
        for file in files:
            if file.endswith(".pyd") or file == "scene.py":
                target_path = os.path.join(ROOT, file)
                shutil.copy(os.path.join(thtoolroot, file), target_path)
                print("coping ", file, " -> ", target_path)#os.path.join(target_path, file))
        break
