## what's this
this folder is the source code of how I collect thdataset automatically and how I train TargetTracker.

show the dataset in [release](https://github.com/GoodenoughPhysicsLab/TouHouTool/releases/tag/thdataset).

## collect thdataset
please ensure you have [build all cpp extensions](./README.md)
```cmd
python fsl_dataset.py
```
the command will collect the dataset automatically while you run the game. show dataset in `/thdataset`.

> there is no need to say that collecting a dataset by hand is a hard work. but, I can gain the label data by reading memory, play th-game by other project like this project, then, I can gain the dataset automatically.

## train TargetTracker
if you download thdataset release, please ENSURE it is in the TargetTracker folder and it's name is thdataset !!!