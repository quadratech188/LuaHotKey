#pragma once

#include <span>

#include <windows.h>

#include "KeyStroke.h"

namespace Keyboard {
	extern BYTE keyboardState[256];
	void open(lua_State* L);
	int getKeyState(lua_State* L);
	bool isOn(DWORD vkCode);
	void updateKeyboardState();
	void sendKeyStrokes(std::span<KeyStroke> keyStrokes);
}
