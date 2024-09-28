#include <windows.h>
#include <winuser.h>
#include "LuaHeader.h"
#include "Keyboard.h"
#include "Modifiers.h"

namespace Modifiers {
	/*
	Bit 0 | Always on
	Bit 1 | LWin
	Bit 2 | LMenu
	Bit 3 | LCtrl
	Bit 4 | LShift
	Bit 5 | RWin
	Bit 6 | RMenu
	Bit 7 | RCtrl
	Bit 8 | RShift
	*/
	int createFromLua(lua_State* L, int index) {
		if (lua_isnil(L, index)) {
			return 0;
		}

		int modifiers = 1;
		
		#define ApplyModifier(offset, name) lua_getfield(L, index, name); modifiers += (1 << offset) * lua_toboolean(L, -1); lua_pop(L, 1);
		
		//TODO: Better error handling
		luaL_argcheck(L, lua_istable(L, index), 1, NULL);

		ApplyModifier(1, "LWIN");
		ApplyModifier(2, "LMENU");
		ApplyModifier(3, "LCONTROL");
		ApplyModifier(4, "LSHIFT");
		ApplyModifier(5, "RWIN")
		ApplyModifier(6, "RMENU");
		ApplyModifier(7, "RCONTROL");
		ApplyModifier(8, "RSHIFT");
		return modifiers;
	}
	int createFromKeyboardState() {
		int modifiers = 1;
		modifiers += (1 << 1) * Keyboard::isOn(VK_LWIN);
		modifiers += (1 << 2) * Keyboard::isOn(VK_LMENU);
		modifiers += (1 << 3) * Keyboard::isOn(VK_LCONTROL);
		modifiers += (1 << 4) * Keyboard::isOn(VK_LSHIFT);
		modifiers += (1 << 5) * Keyboard::isOn(VK_RWIN);
		modifiers += (1 << 6) * Keyboard::isOn(VK_RMENU);
		modifiers += (1 << 7) * Keyboard::isOn(VK_RCONTROL);
		modifiers += (1 << 8) * Keyboard::isOn(VK_RSHIFT);
		return modifiers;
	}
}
