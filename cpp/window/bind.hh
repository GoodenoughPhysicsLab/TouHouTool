#pragma once

#include <string>
#include <optional>
#include <Windows.h>
#include <string_view>
#include <windef.h>
#include <winnt.h>
#include <winscard.h>
#include <winuser.h>
#include "../fast_io/fast_io.h"
#include "../fast_io/fast_io_dsal/string_view.h"
#include <pybind11/pybind11.h>

#pragma comment(lib, "user32.lib")

namespace py = pybind11;

namespace thtool::details {

[[nodiscard]] inline ::std::optional<::std::string> get_hwnd_title(HWND hwnd) noexcept {
    char windowTitle[256];
    if (GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle)) > 0) {
        return ::std::string(windowTitle);
    }
    return ::std::nullopt;
}

// return title if true else return nullopt
[[nodiscard]] inline ::std::optional<::std::string> guess_is_th_window(::std::string title) noexcept {
    const ::std::string_view th_titles[] = {
#if 0
        "Highly Responsive to Prayers",
        "The Story of Eastern Wonderland",
        "Phantasmagoria of Dim.Dream",
        "Lotus Land Story",
        "Mystic Square",
#endif
        "the Embodiment of Scarlet Devil",
        "Perfect Cherry Blossom",
        "Imperishable Night",
        "Phantasmagoria of Flower View",
        "Mountain of Faith",
        "Subterranean Animism",
        "Undefined Fantastic Object",
        "Ten Desires",
        "Double Dealing Character",
        "Legacy of Lunatic Kingdom",
        "Hidden Star in Four Seasons",
        "Wily Beast and Weakest Creature",
        "Unconnected Marketeers",
    };

    for (auto th_title : th_titles) {
        if (title.find(th_title) != ::std::string::npos) {
            return title;
        }
    }
    return ::std::nullopt;
}

extern "C" inline BOOL CALLBACK print_all_windows_proc(HWND hwnd, LPARAM lParam) {
    auto title = get_hwnd_title(hwnd);
    if (!title.has_value()) {
        return TRUE;
    }

    if (guess_is_th_window(title.value())) {
        fast_io::io::print("[[ GUESS ]] ");
    }
    fast_io::io::println("window title: ", title.value());
    return TRUE;
}

extern "C" inline BOOL CALLBACK print_all_windows_proc_only_guess(HWND hwnd, LPARAM lParam) {
    auto title = get_hwnd_title(hwnd);
    if (!title.has_value()) {
        return TRUE;
    }

    if (guess_is_th_window(title.value())) {
        fast_io::io::println("[[ GUESS ]] window title: ", title.value());
    }
    return TRUE;
}

} // namespace thtool::details

namespace thtool::bind {

class BindError : public ::std::exception {
    fast_io::string_view err_msg;
public:
    BindError(fast_io::string_view msg) {
        this->err_msg = msg;
    }

    ~BindError() = default;

    const char* what() const noexcept override {
        return err_msg.data();
    }
};

static ::std::optional<HWND> TH_hwnd = ::std::nullopt;

inline void print_all_windows(bool only_guess=false) noexcept {
    if (only_guess) {
        EnumWindows(details::print_all_windows_proc_only_guess, 0);
    } else {
        EnumWindows(details::print_all_windows_proc, 0);
    }
}

inline void bind_foreground() {
    if (!TH_hwnd.has_value()) {
        TH_hwnd = GetForegroundWindow();
    }
    auto title_name = details::get_hwnd_title(TH_hwnd.value());
    if (!title_name.has_value()) {
        throw BindError("bind to foreground window fail");
    }
    PyObject_Print(PyUnicode_FromFormat("Successfully bind to foreground window: %s\n", title_name.value().c_str()), stdout, Py_PRINT_RAW);
}

} // namespace thtool::bind

namespace thtool::details {

extern "C" inline BOOL CALLBACK bind_guess_proc(HWND hwnd, LPARAM lParam) {
    auto title = get_hwnd_title(hwnd);
    if (!title.has_value()) {
        return TRUE;
    }

    if (guess_is_th_window(title.value())) {
        bind::TH_hwnd = hwnd;
        PyObject_Print(PyUnicode_FromFormat("Successfully bind to guessed window: %s\n", title.value().c_str()), stdout, Py_PRINT_RAW);
        return FALSE;
    }
    return TRUE;
}

} // namespace thtool::details

namespace thtool::bind {

inline void bind_guess() {
    EnumWindows(details::bind_guess_proc, 0);
    if (!TH_hwnd.has_value()) {
        throw BindError("no match TouHou window");
    }
}

inline void bind_title(py::str title) {
    TH_hwnd = FindWindow(NULL, py::cast<::std::string>(title).c_str());
    if (TH_hwnd.value() == NULL) {
        throw BindError("no match window title");
    }
    PyObject_Print(PyUnicode_FromFormat("Successfully bind to window: %s\n", title.cast<::std::string>().c_str()), stdout, Py_PRINT_RAW);
}

} // namespace thtool::bind