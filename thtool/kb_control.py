import time
import pynput
from enum import Enum, unique
from typing import Type, Optional, Union
from . import window

__all__ = ["Behavior", "send"]

@unique
class Behavior(Enum):
    left = pynput.keyboard.Key.left
    up = pynput.keyboard.Key.up
    right = pynput.keyboard.Key.right
    down = pynput.keyboard.Key.down
    bomb = 'x'
    shoot = 'z'
    shift = pynput.keyboard.Key.shift # change move speed
    ctrl = pynput.keyboard.Key.ctrl # escape communication

class _Behavior_list:
    _lst: list = []
    _keyboard = pynput.keyboard.Controller()

    def __new__(cls) -> Type["_Behavior_list"]:
        return _Behavior_list

    @classmethod
    def push(cls, behavior: Behavior, press_time: float, delta_time: Optional[float]) -> None:
        # press_time means the time(ms) when the key is pressed
        for i, (_behavior, _press_time, _delta_time) in enumerate(cls._lst):
            if behavior == _behavior:
                cls._lst[i] = (behavior, press_time, delta_time)
                return
        cls._lst.append((behavior, press_time, delta_time))
        cls._keyboard.press(behavior.value)

    @classmethod
    def release(cls) -> None:
        """ release behaviors which should be released in the queue """
        new_list = []
        for behavior, press_time, delta_time in cls._lst:
            if delta_time is not None and time.time() * 1000 - press_time > delta_time:
                cls._keyboard.release(behavior.value)
            else:
                new_list.append((behavior, press_time, delta_time))
        cls._lst = new_list

_send_queue: list = []
def send(behavior: Behavior, deltatime: Optional[Union[int, float]] = 1000, in_queue: bool = False) -> None:
    ''' send a behavior to TouHou window
        @param behavior: the behavior to send
        @param deltatime: the time(ms) to press the key, None means send anyway
    '''
    if not isinstance(behavior, Behavior) or \
            deltatime is not None and not isinstance(deltatime, (int, float)):
        raise TypeError

    global _send_queue

    if window.is_foreground():
        while _send_queue:
            temp = _send_queue.pop(0)
            _Behavior_list.push(temp[0], time.time() * 1000, temp[1])
        _Behavior_list.push(behavior, time.time() * 1000, deltatime)
    elif in_queue:
        _send_queue.append((behavior, deltatime))
    _Behavior_list.release()

_last_is_foreground: Optional[bool] = None
_time_checkout_to_other: float = 0.
def do_if_checkout_foreground() -> None:
    ''' when touhou game is not in foreground, stop sending behaviors
        otherwise, send behaviors in _Behavior_list
    '''
    global _last_is_foreground, _time_checkout_to_other, _send_queue

    # just stimulate send behaviors in queue
    if len(_send_queue) > 0:
        send(*_send_queue[0])

    current_is_foreground: bool = window.is_foreground()
    if current_is_foreground == _last_is_foreground:
        return

    if current_is_foreground: # checkout touhou window to foreground
        if not _time_checkout_to_other:
            return

        for i, (behavior, press_time, delta_time) in enumerate(_Behavior_list._lst):
            _Behavior_list._lst[i] = \
                (behavior, press_time,
                delta_time + time.time() * 1000 - _time_checkout_to_other
                    if delta_time is not None else None)
    else:
        _time_checkout_to_other = time.time() * 1000
    _last_is_foreground = current_is_foreground
