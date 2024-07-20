#pragma once

#include <cassert>
#include <windows.h>
#include "../bind.hh"

namespace thtool::details {

inline DWORD get_th_pid() {
    static DWORD pid{};
    if (!pid) {
        GetWindowThreadProcessId(bind::TH_hwnd.value(), &pid);
    }
    return pid;
}

inline HANDLE get_process_handle() {
    static HANDLE h{};
    if (!h) {
        h = OpenProcess(PROCESS_VM_READ, true, get_th_pid());
    }
    return h;
}

} // namespace thtool::details