## what's this
this folder is the source code of how I gain the train dataset.

show the dataset in [release](https://github.com/GoodenoughPhysicsLab/TouHouTool/releases/tag/thdataset).

## run
please ensure you have [build all cpp extensions](./README.md)
```cmd
python .\dataset\gain_dependence.py
python -m dataset
```
`python -m dataset` will collect the dataset automatically while you run the game. show dataset in `dataset/thdataset`.

> there is no need to say that collecting a dataset by hand is a hard work. but, I can gain the label data by reading memory, play th-game by other project like this project, then, I can gain the dataset automatically.
