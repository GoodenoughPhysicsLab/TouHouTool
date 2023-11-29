export module docs;

import <string_view>;

export namespace thtool::docs {

constexpr ::std::string_view version{ "thtool version 0.0.0" };

constexpr ::std::string_view help_doc{R"(
usage:
    thtool version
    thtool help

    thtool mouse []

explain:
    version : get version of thtool
    help : get help doc of thtool
)"};

}