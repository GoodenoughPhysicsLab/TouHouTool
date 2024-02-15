#include "define.hh"

#if !defined(__cplusplus) || !defined(THTOOL_CPP20) || !defined(THTOOL_IS_WINDOWS)
#    error "do not use C++20 or do not use windows"
#endif

#include "main.hh"
#include "prints.hh"
#include "keyboard.hh"

#include <string_view>

#include "fast_io/fast_io.h"

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

    if (argc <= 1) {
        thtool::prints::error("thtool access no argument");
        return -1;
    }

    thtool::main_cmd(argv[1]);

    //for (int i{2}; i < argc; ++i) {
    //    ::std::string_view arg_str{argv[i]};
    //}

    return 0;
}
