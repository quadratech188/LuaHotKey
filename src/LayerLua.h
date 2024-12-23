#pragma once

#include "LuaHeader.h"
#include "Layer.h"

namespace LayerLua {
	void open(lua_State* L);
	int new_userdata(lua_State* L);

	Layer* get(lua_State* L, const int index);

	int next(lua_State* L);
}
