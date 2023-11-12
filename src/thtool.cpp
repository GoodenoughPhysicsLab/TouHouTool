
#include <vcruntime.h> // _HAS_CXX23

#if !defined(_MSC_VER) && !defined(_HAS_CXX23)
#    error "do not use MSVC or do not use c++23"
#endif

#include "fast_io/fast_io.h"
#include <string_view>

int main(int argc, char **argv) noexcept
{
#ifdef TOUHOU_TOOL_ARGC0
    if (argc == 0) {
        //fast_io::io::perrln(
        return -1;
    }
#endif // TOUHOU_TOOL_ARGC0
    for (int i{1}; i < argc; ++i) {
        //::std::string_view arg_str
        //if (
    }

    return 0;
}
