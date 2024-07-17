# TouHouTool
a tool for `TouHou Project`.

# functions
* Some semi-automatic assistance.
* Play thxx game automatically.

# how to use
you can also type `python -m thtool --help` to get help.

# make
Requires `c++20` on windows

support: MSVC, [GCC, clang](https://github.com/24bit-xjkp/toolchains/releases)

> install dependencies:
```cmd
python -m pip install --upgrade pip
pip install -r requirements.txt
```

> build release version:
```cmd
python .\make.py
```
this will build all python excutable extension and copy them to the thtool.

> build debug version:
```cmd
python .\make.py --debug
```

> escape cmake setup:

if you have not edited any CMakeLists.txt after the first build, you can use this command to skip the cmake setup to speed up your bulid:
```cmd
python .\make.py --skip-cmake-setup
```