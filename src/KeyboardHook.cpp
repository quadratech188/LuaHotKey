#include "KeyboardHook.h"

#include <windows.h>

#include "KeyStroke.h"
#include "Layers.h"

namespace KeyboardHook {
	bool block;
	bool shouldProcess = true;
	bool processed = false;
	KeyStroke keyStroke;
	KeyStroke prevKeyStroke;
	HHOOK hookHandle;

	bool hook() {
		hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	void unHook() {
		UnhookWindowsHookEx(hookHandle);
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0 || shouldProcess == false) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		block = false;
		processed = false;

		keyStroke = KeyStroke::fromCurrentState(wParam, lParam);
			
		Layers::run(keyStroke);

		prevKeyStroke = keyStroke;

		if (!processed) { // Nothing matched, we pass on the keystroke
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		if (block) {
			return -1;
		}
		else {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
	}
}
