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

inline void send_behavior(Behavior behavior) noexcept {
	//
}

} // namespace thtool::keycoard