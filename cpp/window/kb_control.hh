#pragma once

#include <Windows.h>
#include <minwinbase.h>
#include <minwindef.h>
#include <winnt.h>
#include <winuser.h>
#include "bind.hh"

#pragma comment(lib, "user32.lib")

namespace thtool::kb_control {

enum class Behavior : BYTE {
	left = VK_LEFT,
	up = VK_UP,
	right = VK_RIGHT,
	down = VK_DOWN,
	bomb = 'X',
	shoot = 'Z',
	shift = VK_SHIFT
};

inline void send(Behavior behavior) {
	SetForegroundWindow(bind::TH_hwnd.value());
	SendMessage(bind::TH_hwnd.value(), WM_KEYDOWN, static_cast<WPARAM>(behavior), 0);
	SendMessage(bind::TH_hwnd.value(), WM_KEYUP, static_cast<WPARAM>(behavior), 0);
}

} // namespace thtool::kb_control
