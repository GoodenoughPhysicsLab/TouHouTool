import setuptools as st

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
    ext_modules=[
        st.Extension("thtool.window", ["cpp/window/impl.cc"],
                     extra_compile_args=["/std:c++20"]),
    ]
)