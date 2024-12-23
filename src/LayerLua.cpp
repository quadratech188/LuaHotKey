#include "LayerLua.h"

#include "Layer.h"
#include "LuaHeader.h"

namespace LayerLua {
	const char* mtName = "lhk.Layer";

	const luaL_Reg functions[] {
		{"new", new_userdata},
		{NULL, NULL}
	};

	const luaL_Reg methods[] {
		{"next", next},
		{NULL, NULL}
	};

	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, functions, 0);
		lua_setfield(L, -2, "Layer");

		luaL_newmetatable(L, mtName);
		lua_pushvalue(L, -1);
		lua_setfield(L, -2, "__index");
		luaL_setfuncs(L, methods, 0);
		lua_pop(L, 1);
	}

	int new_userdata(lua_State* L) {
		luaExt_emplaceuserdata<Layer>(L);

		luaL_getmetatable(L, mtName);
		lua_setmetatable(L, -2);

		return 1;
	}

	Layer* get(lua_State* L, const int index) {
		return luaExt_checkudata<Layer>(L, index, mtName);
	}

	int next(lua_State* L) {
		get(L, 1)->next = get(L, 2);
		return 0;
	}
}
