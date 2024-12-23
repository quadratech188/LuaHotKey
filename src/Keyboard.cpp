#include "Keyboard.h"

#include <span>
#include <stdexcept>
#include <string>

#include <windows.h>

#include "KeyStroke.h"
#include "KeyboardHook.h"

namespace Keyboard {
	BYTE keyboardState[256];

	const luaL_Reg luaFunctions[] = {
		{"getKeyState", getKeyState},
		{NULL, NULL}
	};
	
	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);

		lua_setfield(L, -2, "keyboard");
	}

	int getKeyState(lua_State* L) {
		SHORT keyState = keyboardState[lua_tointeger(L, 1)];
		lua_pushboolean(L, keyState & 0x80);
		lua_pushboolean(L, keyState & 1);

		return 2;
	}

	bool isOn(DWORD vkCode) {
		SHORT keyState = GetKeyState(vkCode);
		return keyState & 0x80;
	}

	void sendKeyStrokes(std::span<KeyStroke> keyStrokes) {
		INPUT* inputs = (INPUT*)calloc(keyStrokes.size(), sizeof(INPUT));

		for (int i = 0; i < keyStrokes.size(); i++) {
			inputs[i].type = INPUT_KEYBOARD;
			if (keyStrokes[i].vkCode != 0) {
				inputs[i].ki.wVk = keyStrokes[i].vkCode;
			}
			else if (keyStrokes[i].scanCode != 0) {
				inputs[i].ki.wScan = keyStrokes[i].scanCode;
				inputs[i].ki.dwFlags += KEYEVENTF_SCANCODE;
			}
			if (keyStrokes[i].stroke.isRelease()) {
				inputs[i].ki.dwFlags += KEYEVENTF_KEYUP;
			}
		}
		
		// Our hook is called again when we call SendInput. We don't want to process this, so we set shouldProcess to false when we call SendInput, and revert it after it is called.
		KeyboardHook::shouldProcess = false;
		int err = SendInput(keyStrokes.size(), inputs, sizeof(INPUT));
		KeyboardHook::shouldProcess = true;

		if (err != keyStrokes.size()) {
			throw std::runtime_error("SendInput failed: " + std::to_string(GetLastError()));
		}
	}
}
