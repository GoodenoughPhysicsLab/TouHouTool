import time
import pynput
from typing import Type
from enum import Enum, unique

__all__ = ["Behavior", "send"]

@unique
class Behavior(Enum):
    left = pynput.keyboard.Key.left
    up = pynput.keyboard.Key.up
    right = pynput.keyboard.Key.right
    down = pynput.keyboard.Key.down
    bomb = 'x'
    shoot = 'z'
    shift = pynput.keyboard.Key.shift

class _Behavior_list:
    __lst: list = []
    __keyboard = pynput.keyboard.Controller()

    def __new__(cls) -> Type["_Behavior_list"]:
        return _Behavior_list

    @classmethod
    def push(cls, behavior: Behavior, press_time: int, delta_time: int) -> None:
        for i, (_behavior, _press_time, _delta_time) in enumerate(cls.__lst):
            if behavior == _behavior:
                # cls.__lst[i] = (behavior, _press_time, delta_time + press_time - _press_time)
                # => (_deltatime + deltatime) - (_presstime + _deltatime - press_time)
                cls.__lst[i] = (behavior, press_time, delta_time)
                return
        cls.__lst.append((behavior, press_time, delta_time))
        cls.__keyboard.press(behavior.value)

    @classmethod
    def release(cls) -> None:
        """ release behaviors which should be released in the queue """
        new_list = []
        for behavior, press_time, delta_time in cls.__lst:
            if time.time() * 1000 - press_time > delta_time:
                cls.__keyboard.release(behavior.value)
            else:
                new_list.append((behavior, press_time, delta_time))
        cls.__lst = new_list

def send(behavior: Behavior, deltatime: int = 1000) -> None:
    ''' send a behavior to TouHou window
        @param behavior: the behavior to send
        @param deltatime: the time(ms) to press the key
    '''
    if not isinstance(behavior, Behavior) or not isinstance(deltatime, int):
        raise TypeError

    _Behavior_list.push(behavior, time.time() * 1000, deltatime)
    _Behavior_list.release()