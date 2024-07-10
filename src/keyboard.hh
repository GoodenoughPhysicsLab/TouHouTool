#pragma once

#include <Windows.h>

namespace thtool::keyboard {

enum class Behavior : BYTE {
	left = VK_LEFT,
	up = VK_UP,
	right = VK_RIGHT,
	down = VK_DOWN,
	bomb = 'X',
	shoot = 'Z',
	shift = VK_SHIFT
};

inline void click(Behavior behavior) noexcept {
	keybd_event(static_cast<BYTE>(behavior), 0, 0, 0);
	keybd_event(static_cast<BYTE>(behavior), 0, KEYEVENTF_KEYUP, 0);
}

} // namespace thtool::keycoard