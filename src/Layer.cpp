#include "Layer.h"

#include <optional>

#include "KeyboardSubHook.h"
#include "LuaHeader.h"

namespace LayerNS {
	const char* metatableName = "lhk.Layer";

	const luaL_Reg luaFunctions[] = {
		{"new", newUserdata},
		{NULL, NULL}

	};
	
	const luaL_Reg luaMethods[] = {
		{"register", reg},
		{NULL, NULL}
	};

	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);
		lua_setfield(L, -2, "Layer");

		luaL_newmetatable(L, metatableName);
		lua_pushvalue(L, -1); // Duplicate the metatable
		lua_setfield(L, -2, "__index"); // mt.__index = mt
		luaL_setfuncs(L, luaMethods, 0);
		lua_pop(L, 1); // Pop metatable
	}
	
	int newUserdata(lua_State* L) {
		LayerUdata* userdataPtr = LUA_NEWUSERDATA(LayerUdata, L);

		new (userdataPtr) LayerUdata();

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;
	}

	int reg(lua_State* L) {
		LayerUdata* userdataPtr = LUA_CHECKUSERDATA(LayerUdata, L, 1, metatableName);

		std::array<std::optional<int>, 5> keyFilter = KeyboardSubHook::getFilter(L, 2);

		SubHook subHook = SubHook(L, 3);

		(*userdataPtr->layer)[keyFilter] = subHook;

		return 0;
	}

	LayerUdata* get(lua_State* L, int index) {
		return LUA_CHECKUSERDATA(LayerUdata, L, index, metatableName);
	}

	
}
