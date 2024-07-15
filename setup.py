import os
import sys
import shutil
import setuptools as st
from setuptools.command.build_ext import build_ext

class THExtension(st.Extension):
    def __init__(self, name, sources):
        super().__init__(name, sources)

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        os.system(f"cmake -S cpp -B build "
                  f"-DPYTHON_EXECUTABLE={sys.executable} ")
        os.system("cmake --build build --config Release")

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
    cmdclass={
        "build_ext": CMakeBuild,
    },
    ext_modules=[
        THExtension("thtool.window", ["cpp/window/impl.cc"]),
        THExtension("thtool.default_print", ["cpp/default_print/impl.cc"]),
    ],
)