#pragma once

#include <Windows.h>
#ifdef _DEBUG
#	include "../fast_io/fast_io.h"
#endif

#include "../keyboard.hh"

namespace details{

// Detect whether the button has been clicked or not
bool is_click(int vKey, bool& status) {	
	// GetAsyncKeyState: check if the button "vKey" has been pressed
	if (GetAsyncKeyState(vKey) & 0x8000 && status) {
		status = false;
		return true;
	}
	else if (!(GetAsyncKeyState(vKey) & 0x8000)) {
		status = true;
	}
	return false;
}

} // namespace details

namespace thtool::mouse {

void main() noexcept {
	bool status_X = false, is_click_X = true;
	
	while (true)
	{
		// Check if the button "X" has been clicked
		if (details::is_click(static_cast<int>(thtool::keyboard::Behavior::shoot), is_click_X)) {
			if (status_X) {
				status_X = false;
			}
			else {
				status_X = true;
			}
		}

		if (status_X) {
			thtool::keyboard::click(thtool::keyboard::Behavior::shoot);
			Sleep(100);
		}
	}
}

} // namesapce thtool::mouse