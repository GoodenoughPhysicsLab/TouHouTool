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
	if (s == "version") {
		fast_io::io::println(thtool::docs::version);
	}
	else if (s == "help") {
		fast_io::io::println(thtool::docs::help_doc);
	}
	else if (s == "mouse") {
		//
	}
	else {
		thtool::prints::error("Unknown argument: \"", s, "\"");
	}
}


} // namespace thtool