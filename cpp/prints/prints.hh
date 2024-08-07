#pragma once

#include <string_view>
#include "../fast_io/fast_io.h"

namespace thtool::details {

struct color_base {
    static constexpr ::std::string_view color_end{"\033[39m"};
};

constexpr ::std::uint_least32_t utf8_coding{65001u};  // utf8

static ::std::uint_least32_t output{};
static ::std::uint_least32_t input{};

} //  namespace thtool::details

namespace thtool::prints {

#if __has_cpp_attribute(__gnu__::__cold__)
    [[__gnu__::__cold__]]
#endif
inline void enable_win32_ansi() noexcept {
    constexpr ::std::uint_least32_t enable_virtual_terminal_processing{0x0004u};
    ::std::uint_least32_t out_omode{};
    ::std::uint_least32_t err_omode{};
    void* out_handle{};
    void* err_handle{};
    out_handle = fast_io::win32::GetStdHandle(::fast_io::win32_stdout_number);
    err_handle = fast_io::win32::GetStdHandle(::fast_io::win32_stderr_number);
    fast_io::win32::GetConsoleMode(out_handle, &out_omode);
    fast_io::win32::GetConsoleMode(err_handle, &err_omode);
    fast_io::win32::SetConsoleMode(out_handle, out_omode | enable_virtual_terminal_processing);
    fast_io::win32::SetConsoleMode(err_handle, err_omode | enable_virtual_terminal_processing);
}

// https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
#if __has_cpp_attribute(__gnu__::__cold__)
    [[__gnu__::__cold__]]
#endif
inline void set_win32_console_io_cp_to_utf8() noexcept {
    details::output = ::fast_io::win32::GetConsoleOutputCP();
    details::input = ::fast_io::win32::GetConsoleCP();
    if (details::output != details::utf8_coding) {
        ::fast_io::win32::SetConsoleOutputCP(details::utf8_coding);
    }
    if (details::input != details::utf8_coding) {
        ::fast_io::win32::SetConsoleCP(details::utf8_coding);
    }
}

#if __has_cpp_attribute(__gnu__::__cold__)
    [[__gnu__::__cold__]]
#endif
inline void cancle_set_win32_console_io_cp_to_utf8() {
    {
        if (details::output != details::utf8_coding) {
            ::fast_io::win32::SetConsoleOutputCP(details::output);
        }
        if (details::input != details::utf8_coding) {
            ::fast_io::win32::SetConsoleCP(details::input);
        }
    }
}


struct black : details::color_base {
    static constexpr ::std::string_view color{"\033[30m"};
};

struct red : details::color_base {
    static constexpr ::std::string_view color{"\033[31m"};
};

struct green : details::color_base {
    static constexpr ::std::string_view color{"\033[32m"};
};

struct yellow : details::color_base {
    static constexpr ::std::string_view color{"\033[33m"};
};

struct blue : details::color_base {
    static constexpr ::std::string_view color{"\033[34m"};
};

struct magenta : details::color_base {
    static constexpr ::std::string_view color{"\033[35m"};
};

struct cyan : details::color_base {
    static constexpr ::std::string_view color{"\033[36m"};
};

struct white : details::color_base {
    static constexpr ::std::string_view color{"\033[37m"};
};

template<typename color_t, typename... Args>
	requires requires { color_t::color; color_t::color_end; }
void color_print(Args&&... args) noexcept
{
#ifdef THTOOL_CLOSE_COLOR_PRINT
	fast_io::io::print(args...);
#else
	fast_io::io::print(color_t::color, args..., color_t::color_end);
#endif
}

template<typename color_t, typename... Args>
	requires requires { color_t::color; color_t::color_end; }
void color_println(Args&&... args) noexcept
{
#ifdef THTOOL_CLOSE_COLOR_PRINT
	fast_io::io::println(args...);
#else
	fast_io::io::println(color_t::color, args..., color_t::color_end);
#endif
}

template<typename... Args>
void warning(Args&&... arg) noexcept
{
    color_print<yellow>("Warning: ");
    fast_io::io::println(::std::forward<Args>(arg)...);
}

template<typename... Args>
void error(Args&&... arg) noexcept
{
    color_print<red>("Error: ");
    fast_io::io::println(::std::forward<Args>(arg)...);
}

} // namespace thtool::prints
