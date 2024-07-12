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

..\venv\Scripts\python.exe -m build --wheel --sdist

for /d /r "build" %%d in (lib.*) do (
    copy %%d\thtool\*.pyd .\thtool
)