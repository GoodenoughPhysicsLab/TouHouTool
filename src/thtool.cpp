#include <vcruntime.h> // _HAS_CXX23

#if !defined(_MSC_VER) || !_HAS_CXX23
#    error "do not use MSVC or do not use c++23"
#endif

import main;
import prints;
import keyboard;

import <string_view>;

import "fast_io/fast_io.h";

int main(int argc, char **argv) noexcept
{
    thtool::init();

    if (argc <= 1) {
        thtool::prints::error("thtool access no argument");
        return -1;
    }

    thtool::main_cmd(argv[1]);

    for (int i{2}; i < argc; ++i) {
        ::std::string_view arg_str{argv[i]};
    }

    return 0;
}
