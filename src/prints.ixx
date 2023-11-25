export module prints;

import <array>;
import <string_view>;
import <type_traits>;

import "fast_io/fast_io.h";

namespace details {

struct color_base {
		static constexpr ::std::string_view color_end{"\033[39m"};
	};

} //  details

export namespace thtool::prints {

struct black : ::details::color_base {
    static constexpr ::std::string_view color{"\033[30m"};
};

struct red : ::details::color_base {
    static constexpr ::std::string_view color{"\033[31m"};
};

struct green : ::details::color_base {
    static constexpr ::std::string_view color{"\033[32m"};
};

struct yellow : ::details::color_base {
    static constexpr ::std::string_view color{"\033[33m"};
};

struct blue : ::details::color_base {
    static constexpr ::std::string_view color{"\033[34m"};
};

struct magenta : ::details::color_base {
    static constexpr ::std::string_view color{"\033[35m"};
};

struct cyan : ::details::color_base {
    static constexpr ::std::string_view color{"\033[36m"};
};

struct white : ::details::color_base {
    static constexpr ::std::string_view color{"\033[37m"};
};

template<typename color_t>
	requires requires { color_t::color; color_t::color_end; }
void color_print(::std::string_view str) noexcept
{
#ifdef THTOOL_CLOSE_COLOR_PRINT
	fast_io::io::println(str);
#else
	fast_io::io::print(color_t::color, str, color_t::color_end);
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