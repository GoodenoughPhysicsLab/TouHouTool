@echo off

if exist .\build (
    rd /s /q .\build
)
if exist .\dist (
    rd /s /q .\dist
)
if exist .\thtool.egg-info (
    rd /s /q .\thtool.egg-info
)
if exist .\thtool\*.pyd (
    del .\thtool\*.pyd
)

if not exist "cpp\pybind11" (
    git clone https://github.com/pybind/pybind11.git cpp\pybind11 --depth=1
)

python -m build --wheel --sdist

for /d /r "build" %%d in (lib.*) do (
    copy %%d\thtool\*.pyd .\thtool
)