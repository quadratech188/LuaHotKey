#pragma once

#include <windows.h>

#include "KeyStroke.h"

namespace KeyboardHook {
	extern KeyStroke keyStroke;
	extern bool block;
	extern bool shouldProcess;
	extern bool processed;

	extern KeyStroke prevKeyStroke;

	bool hook();
	void unHook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
