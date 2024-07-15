# TouHouTool
a tool of `TouHou Project`.

# functions
* Some semi-automatic assistance.
* Play thxx game automatically.

# how to use
you can also type `python -m thtool --help` to get help.

# make
Requires `c++20` on windows  
support: MSVC, [GCC, clang](https://github.com/24bit-xjkp/toolchains/releases)  

```cmd
.\make.bat
```
this will build all python excutable extension and copy them to the thtool.  

> build your non-ansi version
```
cmake -B build -DTHTOOL_CLOSE_COLOR_PRINT=on
```