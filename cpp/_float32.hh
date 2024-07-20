#pragma once

// https://en.cppreference.com/w/cpp/types/floating-point
#if (defined(_MSC_VER) && __cplusplus == 199711L && _MSVC_LANG >= 202302L)
    || (!defined(_MSC_VER) && __cplusplus >= 202302L)
#include <stdfloat>
#endif

namespace thtool::f32 {

#if __STDCPP_FLOAT32_T__
    using float32_type = std::float32_t;
#else
    using float32_type = float;
#endif

} // namespace thtool::details