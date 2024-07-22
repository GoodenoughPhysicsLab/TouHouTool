# TouHouTool
a tool for `TouHou Project`.

download TouHou Project game from [there](https://cloud.lilywhite.cc/s/4ZUW?path=%2F%E4%B8%9C%E6%96%B9Project%2F%E5%AE%98%E6%96%B9%E6%B8%B8%E6%88%8F).

other projects like this:
*  [TH10AI](https://github.com/Infinideastudio/TH10AI)
*  [twinject](https://github.com/Netdex/twinject)

# functions
* Some semi-automatic assistance.
* Play thxx game automatically.

# how to use
you can also type `python -m thtool --help` to get help.

# make
Requires `c++20` on windows

support: MSVC, [g++, clang++](https://github.com/24bit-xjkp/toolchains/releases)

for `g++` or `clang++` user, requires [gnu make for windows](https://ftp.gnu.org/gnu/make/)(download make-\<version\>.tar.gz, unpack it and run `build_w32.bat`, then you can use `WinRel\gunmake.exe` to run makefile on windows)

> install build dependencies:
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

> use `g++` or `clang++`
```cmd
python .\make.py --c-compiler gcc --cxx-compiler g++ --make-program gnumake
```
```cmd
python .\make.py --c-compiler clang --cxx-compiler clang++ --make-program gnumake
```

> escape cmake setup:

if you have not edited any CMakeLists.txt after the first build and do not change your C++ compiler to build, you can use this command to skip the cmake setup to speed up your bulid:
```cmd
python .\make.py --skip-cmake-setup
```
