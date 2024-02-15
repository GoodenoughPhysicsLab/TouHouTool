#pragma once

#if defined(_MSC_VER) && __cplusplus == 199711L
#    if _MSVC_LANG >= 201402L
#        define THTOOL_CPP14
#    endif
#    if _MSVC_LANG > 201402L
#        define THTOOL_CPP17
#    endif
#    if _MSVC_LANG >= 202002L
#        define THTOOL_CPP20
#    endif
#elif !(defined(_MSC_VER) && __cplusplus == 199711L)
#    if __cplusplus >= 201402L
#        define THTOOL_CPP14
#    endif
#    if __cplusplus >= 201703L
#        define THTOOL_CPP17
#    endif
#    if __cplusplus >= 202002L
#        define THTOOL_CPP20
#    endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#   define THTOOL_IS_WINDOWS
#endif