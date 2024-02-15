#pragma once

#include <csignal>

#include "docs.hh"
#include "mouse/mouse.hh"
#include "prints.hh"

#include <cstdlib>
#include <string_view>

#include "fast_io/fast_io.h"

namespace thtool {

void main_cmd(::std::string_view s) noexcept {
	if (s == "mouse") {
		thtool::mouse::main();
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