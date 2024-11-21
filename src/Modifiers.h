#pragma once

#include <windows.h>

#include "LuaHeader.h"

namespace Modifiers {
	typedef int Modifiers;

	void open(lua_State* L);
	Modifiers* get(lua_State* L, int index);
	int newUserdata(lua_State* L);
	Modifiers fromKeyboardState();
}
