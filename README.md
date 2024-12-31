# TouHouTool
a tool for `TouHou Project`.

download TouHou Project game from [there](https://cloud.lilywhite.cc/s/4ZUW?path=%2F%E4%B8%9C%E6%96%B9Project%2F%E5%AE%98%E6%96%B9%E6%B8%B8%E6%88%8F).

other projects like this:
*  [TH10AI](https://github.com/Infinideastudio/TH10AI)
*  [twinject](https://github.com/Netdex/twinject)

# functions
* Play th10.exe automatically

# how to use
you can also type `python -m thtool --help` to get help.

# make
Requires `c++20` on windows

support: MSVC, [g++, clang++ (for windows)](https://github.com/24bit-xjkp/toolchains/releases)

for `gnu make` users, requires [gnu make for windows](https://ftp.gnu.org/gnu/make/)(download make-\<version\>.tar.gz, unpack it and run `build_w32.bat`, then you can use `WinRel\gunmake.exe` to run makefile on windows)

> install dependencies:
```cmd
python -m pip install --upgrade pip
pip install -r requirements.txt
python -m build --wheel
```
