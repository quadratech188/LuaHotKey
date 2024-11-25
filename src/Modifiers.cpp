#include <iostream>
#include <windows.h>

#include "Keyboard.h"
#include "LuaHeader.h"
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

	const char* metatableName = "lhk.Modifiers";

	const luaL_Reg luaFunctions[] = {
		{"new", newUserdata},
		{NULL, NULL}
	};

	Modifiers* get(lua_State* L, int index) {
		return luaExt_checkudata<Modifiers>(L, index, metatableName);
	}

	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);
		lua_setfield(L, -2, "Modifiers");
		luaL_newmetatable(L, metatableName);
		// No methods as of now
		lua_pop(L, 1);
	}

	int newUserdata(lua_State* L) {
		if (lua_istable(L, 1)) {
			#define apply(offset, name) lua_getfield(L, 1, name); modifiers += (1 << offset) * lua_toboolean(L, -1); lua_pop(L, 1);

			int modifiers = 0;

			apply(0, "LWin");
			apply(1, "LMenu");
			apply(2, "LCtrl");
			apply(3, "LShift");
			apply(4, "RWin");
			apply(5, "RMenu");
			apply(6, "RCtrl");
			apply(7, "RShift");

			luaExt_emplaceuserdata<Modifiers>(L, modifiers);

			luaL_getmetatable(L, metatableName);
			lua_setmetatable(L, -2);

			return 1;
		}
		else {
			return luaL_argerror(L, 1, "Expected table");
		}
	}

	Modifiers fromKeyboardState() {
		int modifiers = 0;
		modifiers += (1 << 0) * Keyboard::isOn(VK_LWIN);
		modifiers += (1 << 1) * Keyboard::isOn(VK_LMENU);
		modifiers += (1 << 2) * Keyboard::isOn(VK_LCONTROL);
		modifiers += (1 << 3) * Keyboard::isOn(VK_LSHIFT);
		modifiers += (1 << 4) * Keyboard::isOn(VK_RWIN);
		modifiers += (1 << 5) * Keyboard::isOn(VK_RMENU);
		modifiers += (1 << 6) * Keyboard::isOn(VK_RCONTROL);
		modifiers += (1 << 7) * Keyboard::isOn(VK_RSHIFT);
		return modifiers;
	}
}
