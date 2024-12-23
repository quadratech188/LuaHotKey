#pragma once

#include "LuaHeader.h"
#include "Layer.h"

extern "C" __declspec(dllexport) int luaopen_LuaHotKey(lua_State* L);

namespace LuaHotKey {
	extern lua_State* L;
	extern Layer* first;

	void open(lua_State* L);

	int start(lua_State* L);
	int stop(lua_State* L);
	int begin(lua_State* L);
}
