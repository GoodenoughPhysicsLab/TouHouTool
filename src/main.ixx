#include <csignal>

export module main;

import <cstdlib>;

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



} // namespace thtool