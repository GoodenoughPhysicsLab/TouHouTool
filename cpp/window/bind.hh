#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <optional>
#include <windows.h>
#include <string_view>
#include <windef.h>
#include <winnt.h>
#include <winscard.h>
#include <winuser.h>
#include <pybind11/pytypes.h>
#include <Python.h>
#include <pybind11/pybind11.h>

#pragma comment(lib, "user32.lib")

namespace py = pybind11;

namespace thtool::bind {

enum class ThGame : ::std::uint32_t {
    unset = 0, // no binded th-game
#if 0
    hmx, /* the Embodiment of Scarlet Devil */
#endif
    yym = 7, /* Perfect Cherry Blossom */
    yyc = 8, /* Imperishable Night */
    hyz = 9, /* Phantasmagoria of Flower View */
    fsl = 10, /* Mountain of Faith */
    dld = 11, /* Subterranean Animism */
    xlc = 12, /* Undefined Fantastic Object */
    slm = 13, /* Ten Desires */
    hzc = 14, /* Double Dealing Character */
    gzz = 15, /* Legacy of Lunatic Kingdom */
    tkz = 16, /* Hidden Star in Four Seasons */
    gxs = 17, /* Wily Beast and Weakest Creature */
    hld = 18, /* Unconnected Marketeers */
    unknown,
};

static ThGame TH_game{ThGame::unset};

inline ThGame get_th_game() noexcept {
    return TH_game;
}

} // namespace thtool::bind

namespace thtool::details {

[[nodiscard]] inline ::std::optional<::std::string> get_hwnd_title(HWND hwnd) noexcept {
    char windowTitle[256];
    if (GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle)) > 0) {
        return ::std::string(windowTitle);
    }
    return ::std::nullopt;
}

// return title if true else return nullopt
[[nodiscard]] inline ::std::optional<bind::ThGame> guess_is_th_window(::std::string title) noexcept {
    const ::std::string_view th_titles[] = {
#if 0
        "Highly Responsive to Prayers",
        "The Story of Eastern Wonderland",
        "Phantasmagoria of Dim.Dream",
        "Lotus Land Story",
        "Mystic Square",
        "the Embodiment of Scarlet Devil",
#endif
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

    int th_game = static_cast<int>(bind::ThGame::yym);
    for (auto th_title : th_titles) {
        if (title.find(th_title) != ::std::string::npos) {
            return static_cast<bind::ThGame>(th_game);
        }
        ++th_game;
    }
    return ::std::nullopt;
}

extern "C" inline BOOL CALLBACK print_all_windows_proc(HWND hwnd, LPARAM lParam) {
    auto title = get_hwnd_title(hwnd);
    if (!title.has_value()) {
        return TRUE;
    }

    if (guess_is_th_window(title.value()).has_value()) {
        ::std::cout << "[[ GUESS ]] ";
    }
    ::std::cout << "window title: " << title.value();
    return TRUE;
}

extern "C" inline BOOL CALLBACK print_all_windows_proc_only_guess(HWND hwnd, LPARAM lParam) {
    auto title = get_hwnd_title(hwnd);
    if (!title.has_value()) {
        return TRUE;
    }

    if (guess_is_th_window(title.value()).has_value()) {
        ::std::cout << "[[ GUESS ]] window title: " << title.value();
    }
    return TRUE;
}

} // namespace thtool::details

namespace thtool::bind {

class BindError : public ::std::exception {
    ::std::string_view err_msg;
public:
    BindError(::std::string_view msg) {
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
    py::print("Successfully bind to foreground window:", title_name.value());
    TH_game = ThGame::unknown;
}

} // namespace thtool::bind

namespace thtool::details {

extern "C" inline BOOL CALLBACK bind_guess_proc(HWND hwnd, LPARAM lParam) {
    auto title_name = get_hwnd_title(hwnd);
    if (!title_name.has_value()) {
        return TRUE;
    }

    ::std::optional<bind::ThGame> thgame = details::guess_is_th_window(title_name.value());
    if (thgame.has_value()) {
        bind::TH_hwnd = hwnd;
        bind::TH_game = thgame.value();
        using namespace ::std::string_literals;
        py::print(
            "[thtool] Successfully bind to th"s + ::std::to_string(static_cast<::std::uint32_t>(thgame.value()))
        );
        return FALSE;
    }
    return TRUE;
}

} // namespace thtool::details

namespace thtool::bind {

inline void bind_auto() {
    EnumWindows(details::bind_guess_proc, 0);
    if (!TH_hwnd.has_value()) {
        throw BindError("no match TouHou window, please open your th-game window");
    }
}

inline void bind_title(py::str title) {
    TH_hwnd = FindWindow(NULL, py::cast<::std::string>(title).c_str());
    if (TH_hwnd.value() == NULL) {
        throw BindError("no match window title");
    }
    py::print("Successfully bind to foreground window:", title.cast<::std::string>());
    TH_game = ThGame::unknown;
}

} // namespace thtool::bind
