import os
import shutil
import pathlib
import platform
import argparse

if platform.system() != "Windows":
    raise OSError("This script is only for Windows")

if __name__ == "__main__":
    ROOT = os.path.dirname(os.path.abspath(__file__))
    if pathlib.Path(ROOT).resolve() != pathlib.Path(os.path.abspath(".")).resolve():
        raise RuntimeError("Please run this script in the repository's root directory")

    parser = argparse.ArgumentParser("thtool(TouHouTool) build script")
    parser.add_argument("--debug", action="store_true", help="Build in debug mode")
    parser.add_argument("--skip-cmake-setup", action="store_true", help="Skip cmake setup")

    args = parser.parse_args()

    for root, dirs, _ in os.walk(ROOT):
        for dir in dirs:
            if dir == "build":
                if args.skip_cmake_setup:
                    for root2, dirs2, _ in os.walk(os.path.join(root, dir)):
                        for dir2 in dirs2:
                            if dir2.startswith("lib.") or \
                                dir2.startswith("bdist.") or \
                                dir2.startswith("temp."):
                                shutil.rmtree(os.path.join(root2, dir2))
                        break

                else:
                    shutil.rmtree(os.path.join(root, dir))

            if dir == "dist" or dir.endswith(".egg-info"):
                shutil.rmtree(os.path.join(root, dir))
        break

    for root, _, files in os.walk(os.path.join(ROOT, "thtool")):
        for file in files:
            if file.endswith(".pyd"):
                os.remove(os.path.join(root, file))
        break

    if not os.path.exists(os.path.join(ROOT, "cpp/pybind11")) and \
        not os.path.isdir(os.path.join(ROOT, "cpp/pybind11")):
        os.system("git clone https://github.com/pybind/pybind11.git cpp/pybind11 --depth=1")

    if not os.path.exists(os.path.join(ROOT, "cpp/pybind11")) and \
         not os.path.isdir(os.path.join(ROOT, "cpp/pybind11")):
        raise RuntimeError("clone pybind11 fail")

    if args.debug:
        os.environ["THTOOL_DEBUG"] = "1"
    os.system(f"python -m build --wheel --sdist")

    for root, dirs, files in os.walk(os.path.join(ROOT, "build")):
        for dir in dirs:
            if dir.startswith("lib."):
                for root2, _, files2 in os.walk(os.path.join(root, dir, "thtool")):
                    copying_file_counter = 0
                    for file in files2:
                        if file.endswith(".pyd"):
                            shutil.copy(os.path.join(root2, file), os.path.join(ROOT, "thtool"))
                            print(f"Coping {file} -> thtool")
                            copying_file_counter += 1
                    print(f"{copying_file_counter} successed, {3 - copying_file_counter} failed")
                    exit(0)
        break
