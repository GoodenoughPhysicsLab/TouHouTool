import os
import sys
import shutil
import setuptools as st
from setuptools.command.build_ext import build_ext

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        cmake_cfg_flags: str = os.environ.get("AUTOTH10_CMAKE_CFG_FLAGS", "")
        os.system(
            f"cmake -S \"{os.path.join(SCRIPT_DIR, 'cpp')}\" -B \"{os.path.join(SCRIPT_DIR, 'build')}\" "
            f"-DPYTHON_EXECUTABLE=\"{sys.executable}\" -DCMAKE_BUILD_TYPE=Release "
            + cmake_cfg_flags
        )

        cmake_build_flags: str = os.environ.get("AUTOTH10_CMAKE_BUILD_FLAGS", "")
        os.system(f"cmake --build \"{os.path.join(SCRIPT_DIR, 'build')}\" --config Release " + cmake_build_flags)

        cmake_install_flags: str = os.environ.get("AUTOTH10_CMAKE_INSTALL_FLAGS", "")
        os.system(f"cmake --install \"{os.path.join(SCRIPT_DIR, 'build')}\" --config Release " + cmake_install_flags)

st.setup(
    name="auto_th10",
    version="0.0.0",
    author="Arendelle",
    author_email="2381642961@qq.com",
    description="Play th10 automatically",
    long_description="",
    long_description_content_type="text/markdown",
    url="https://github.com/GoodenoughPhysicsLab/auto-th10",
    python_requires=">=3.7",
    packages=["auto_th10"],
    install_requires=["pynput", "opencv-python"],
    cmdclass={
        "build_ext": CMakeBuild,
    },
    ext_modules=[
        # build rules in cpp/CMakeLists.txt
        st.Extension("_", sources=["_"])
    ]
)
