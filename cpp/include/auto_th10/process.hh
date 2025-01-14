#pragma once

#include <cstdio>
#include <cstring>
#include <windows.h>
#include "exception.hh"

namespace auto_th10::process {

namespace details {

inline BOOL enum_window_proc(HWND hwnd, LPARAM th10_hwnd_) noexcept {
    char title[64]{};
    if (GetWindowTextA(hwnd, title, sizeof(title)) <= 0) {
        return TRUE;
    }
    if (::std::strstr(title, "Mountain of Faith") == nullptr) {
        return TRUE;
    }
    HWND* th10_hwnd_ptr = reinterpret_cast<HWND*>(th10_hwnd_);
    *th10_hwnd_ptr = hwnd;
    return FALSE;
}

}  // namespace details

/* Get TH10 window handle
 */
inline HWND get_hwnd() noexcept {
    static HWND th10_hwnd{};
    if (th10_hwnd != nullptr) {
        return th10_hwnd;
    }
    EnumWindows(details::enum_window_proc, reinterpret_cast<LPARAM>(&th10_hwnd));
    if (th10_hwnd == nullptr) {
        puts("auto_th10::BindError: detect th10 window failed");
        exception::terminate();
    }
    return th10_hwnd;
}

/* Get TH10 process ID
 */
inline DWORD get_pid() {
    static DWORD pid{};
    if (pid == 0) {
        GetWindowThreadProcessId(get_hwnd(), &pid);
    }
    return pid;
}

/* Get TH10 process handle
 */
inline HANDLE get_process_handle() {
    static HANDLE handle{};
    if (handle == nullptr) {
        handle = OpenProcess(PROCESS_VM_READ, true, get_pid());
    }
    return handle;
}

}  // namespace auto_th10::process
