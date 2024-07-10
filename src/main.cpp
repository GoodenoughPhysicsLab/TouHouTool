#if !defined(__cpp_concepts) || !defined(_WIN32)
#    error "do not use C++20 or do not use windows"
#endif

#include "main.hh"
#include "prints.hh"

#include <string_view>

namespace details {

void thtool_exit(int signal) noexcept {
	if (signal == SIGINT) {
		::std::exit(0);
	}
}

} // namespace detils

int main(int argc, char **argv) noexcept
{
    ::std::signal(SIGINT, ::details::thtool_exit);
    thtool::prints::enable_win32_ansi();

    if (argc <= 1) [[unlikely]] {
        thtool::prints::error("thtool access no argument");
        return -1;
    }

    thtool::main_cmd(argv[1]);

    //for (int i{2}; i < argc; ++i) {
    //    ::std::string_view arg_str{argv[i]};
    //}

    return 0;
}
