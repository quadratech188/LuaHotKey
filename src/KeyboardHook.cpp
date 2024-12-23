#include "KeyboardHook.h"

#include <windows.h>

#include "Dll.h"
#include "Keyboard.h"

namespace KeyboardHook {
	HHOOK hookHandle;

	bool hook() {
		hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	void unHook() {
		UnhookWindowsHookEx(hookHandle);
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		Keyboard keyboard(wParam, lParam);

		LuaHotKey::first->run(keyboard);

		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
}
