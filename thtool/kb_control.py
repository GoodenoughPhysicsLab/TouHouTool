import time
import pynput
from enum import Enum, unique
from typing import Type, Optional, Union, List
from . import window

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

_send_queue: List[tuple] = [] # tuple: (behavior, delta_time)
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

_last_is_foreground: Optional[bool] = None
_the_time_checkout_to_other: float = 0.
def do_if_checkout_foreground() -> None:
    ''' when touhou game is not in foreground, stop sending behaviors

        otherwise, send behaviors in _Behavior_list

        this function must run in the main loop

        I assume that you type the cmd, then checkout to touhou window
    '''
    global _last_is_foreground, _the_time_checkout_to_other, _send_queue
    current_is_foreground: bool = window.is_foreground()

    # just for release in time
    _Behavior_list.release()

    if current_is_foreground == _last_is_foreground:
        return

    if current_is_foreground is False and _last_is_foreground is None:
        if not _the_time_checkout_to_other:
            _the_time_checkout_to_other = time.time() * 1000
        return

    if current_is_foreground: # checkout touhou window to foreground
        # if _last_is_foreground is None:
        #     return

        for i, (behavior, press_time, delta_time) in enumerate(_Behavior_list._lst):
            _Behavior_list._lst[i] = (behavior, press_time,
                delta_time + time.time() * 1000 - _the_time_checkout_to_other
                if delta_time is not None else None)
            _Behavior_list._keyboard.press(behavior.value)

        while len(_send_queue) > 0:
            temp = _send_queue.pop(0)
            _Behavior_list.push(temp[0], time.time() * 1000, temp[1])

        _last_is_foreground = current_is_foreground

    else:
        _the_time_checkout_to_other = time.time() * 1000
        for behavior, press_time, delta_time in _Behavior_list._lst:
            _Behavior_list._keyboard.release(behavior.value)
            _send_queue.append(
                (behavior, delta_time - (time.time() * 1000 - press_time) if delta_time is not None else None)
            )
        _Behavior_list._lst = []

        _last_is_foreground = current_is_foreground

    # if _last_is_foreground is not None:
    #     _last_is_foreground = current_is_foreground
