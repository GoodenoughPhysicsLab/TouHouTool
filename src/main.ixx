#include <csignal>

export module main;

import docs;
import prints;

import <cstdlib>;
import <string_view>;

import "fast_io/fast_io.h";

namespace details {

void thtool_exit(int signal) noexcept {
	if (signal == SIGINT) {
		::std::exit(0);
	}
}

} // namespace detils

export namespace thtool {

void init() noexcept {
	::std::signal(SIGINT, ::details::thtool_exit);
}

void main_cmd(::std::string_view s) noexcept {
	if (s == "mouse") {
		//
	}
	else if (s == "version") [[unlikely]] {
		fast_io::io::println(thtool::docs::version);
	}
	else if (s == "help") [[unlikely]] {
		fast_io::io::println(thtool::docs::help_doc);
	}
	else {
		thtool::prints::error("Unknown argument: \"", s, "\"\nget help: ", thtool::prints::cyan::color, "thtool help", thtool::prints::cyan::color_end);
	}
}


} // namespace thtool