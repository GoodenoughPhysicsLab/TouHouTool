#include <Windows.h>

export module keyboard;

export namespace thtool::keyboard {

enum class Behavior : BYTE {
	left = VK_LEFT,
	up = VK_UP,
	right = VK_RIGHT,
	down = VK_DOWN,
	bomb = 'B',
	shoot = 'X',
	shift = VK_SHIFT
};

void press_start(Behavior behavior) noexcept {
	keybd_event(static_cast<BYTE>(behavior), 0, 0, 0);
}

void press_stop(Behavior behavior) noexcept {
	keybd_event(static_cast<BYTE>(behavior), 0, KEYEVENTF_KEYUP, 0);
}

void click(Behavior behavior) noexcept {
	press_start(behavior);
	press_stop(behavior);
}

} // namespace thtool::keycoard