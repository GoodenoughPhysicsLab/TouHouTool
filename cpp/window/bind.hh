#pragma once

#include <cstdio>
#include <optional>
#include <Windows.h>

#pragma comment(lib, "user32.lib")

namespace thtool::details {

extern "C" inline BOOL CALLBACK _print_hwnd_title(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    if (GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle)) > 0) {
        printf("Window Title: %s\n", windowTitle);
    }

    return TRUE;
}

} // namespace thtool::details

namespace thtool::bind {

inline ::std::optional<HWND> TH_hwnd = ::std::nullopt;

inline void print_all_windows() noexcept {
    EnumWindows(details::_print_hwnd_title, 0);
}

inline void set_hwnd_foreground() noexcept {
    if (!TH_hwnd.has_value()) {
        TH_hwnd = GetForegroundWindow();
    }
}

} // namespace thtool::bind