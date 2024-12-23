#pragma once

#include <windows.h>

namespace KeyboardHook {
	bool hook();
	void unHook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
