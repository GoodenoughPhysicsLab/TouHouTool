# auto-th10
Playing th10 game automatically by auto-th10 AI.

download th10 from [there](https://cloud.lilywhite.cc/s/4ZUW?path=%2F%E4%B8%9C%E6%96%B9Project%2F%E5%AE%98%E6%96%B9%E6%B8%B8%E6%88%8F).

other projects like this:
*  [TH10AI](https://github.com/Infinideastudio/TH10AI)
*  [twinject](https://github.com/Netdex/twinject)

## features
* Play th10.exe automatically

## how to use
you can also type `python -m auto_th10 --help` to get help.

## api
* `C++` api in `cpp/include/auto_th10/`
* `Python` api in `auto_th10/` (include build binary)

## make
Requires at least `c++20` on windows

support: MSVC, [GCC, llvm](https://github.com/24bit-xjkp/toolchains/releases)

* install dependencies:
```cmd
python -m pip install --upgrade pip
pip install -r requirements.txt
```

* build:
```cmd
python -m build --wheel
```

If you want detailed control of build, use cmake by hand. Take what `python -m build` does for example:
```cmd
cmake -S cpp -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
cmake --install build --config Release
```
