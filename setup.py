import os
import sys
import shutil
import setuptools as st
from setuptools.command.build_ext import build_ext

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        cmake_cfg_flags: str = os.environ.get("THTOOL_CMAKE_CFG_FLAGS", "")
        os.system(
            f"cmake -S \"{os.path.join(SCRIPT_DIR, 'cpp')}\" -B \"{os.path.join(SCRIPT_DIR, 'build')}\" "
            f"-DPYTHON_EXECUTABLE={sys.executable} "
            + cmake_cfg_flags
        )

        cmake_build_flags: str = os.environ.get("THTOOL_CMAKE_BUILD_FLAGS", "")
        os.system(f"cmake --build \"{os.path.join(SCRIPT_DIR, 'build')}\" " + cmake_build_flags)

        # install file from build to thtool
        # TODO rewrite this in CMakeLists.txt
        for root, _, files in os.walk("build"):
            if os.path.abspath(root) == extdir:
                continue

            for file in files:
                if file.endswith(".pyd"):
                    shutil.copy(os.path.join(root, file), extdir)

        for root, dirs, files in os.walk(os.path.join(SCRIPT_DIR, "build")):
            for dir in dirs:
                if dir.startswith("lib."):
                    for root2, _, files2 in os.walk(os.path.join(root, dir, "thtool")):
                        copying_file_counter = 0
                        for file in files2:
                            if file.endswith(".pyd"):
                                shutil.copy(os.path.join(root2, file), os.path.join(SCRIPT_DIR, "thtool"))
                                print(f"Coping {file} -> thtool")
                                copying_file_counter += 1
                        fail_files = 2 - copying_file_counter
                        print(f"Summary: {copying_file_counter} successed, {fail_files} failed")
                        if fail_files > 0:
                            raise RuntimeError(f"{fail_files} cpp extensions build failed")

st.setup(
    name="thtool",
    version="0.0.0",
    author="Arendelle",
    author_email="2381642961@qq.com",
    description="tools for TouHou project",
    long_description="",
    long_description_content_type="text/markdown",
    url="https://github.com/GoodenoughPhysicsLab/TouHouTool",
    python_requires=">=3.7",
    packages=["thtool"],
    install_requires=["pynput", "opencv-python"],
    cmdclass={
        "build_ext": CMakeBuild,
    },
    # because I use cmake, so there is no need to write ext_modules
    ext_modules=[
        # just write one, then setup.py will use cmake to build all ext_modules
        # build rule in cpp/CMakeLists.txt
        st.Extension("thtool.window", sources=["cpp/window/impl.cc"])
    ]
)