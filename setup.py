import os
import sys
import shutil
import setuptools as st
from setuptools.command.build_ext import build_ext

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        os.system(f"cmake -S cpp -B build "
                  f"-DPYTHON_EXECUTABLE={sys.executable} ")
        os.system(f"cmake --build build "
                  f"--config {'Debug' if os.environ.get('THTOOL_DEBUG') else 'Release'}")

        # copy file from build to thtool
        for root, _, files in os.walk("build"):
            if os.path.abspath(root) == extdir:
                continue

            for file in files:
                if file.endswith(".pyd"):
                    shutil.copy(os.path.join(root, file), extdir)

st.setup(
    name="thtool",
    version="0.0.0",
    author="Goodenough",
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