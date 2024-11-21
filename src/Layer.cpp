#include "Layer.h"

#include <optional>

#include "KeyStrokeLua.h"
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
		{"yield", yield},
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
		new (luaExt_newuserdata<LayerUdata>(L)) LayerUdata();

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;
	}

	int reg(lua_State* L) {
		std::array<std::optional<int>, 5> keyFilter = KeyboardSubHook::getFilter(L, 2);

		SubHook subHook = SubHook(L, 3);

		get(L, 1)->layer->data[keyFilter] = subHook;

		return 0;
	}

	int yield(lua_State* L) {
		get(L, 1)->layer->out(*KeyStrokeLua::get(L, 2));
		return 0;
	}

	LayerUdata* get(lua_State* L, int index) {
		return luaExt_checkudata<LayerUdata>(L, index, metatableName);
	}
	
	void Layer::run(KeyStroke keyStroke) {
		std::array<int, 5> filter = keyStroke.toFilter();

		/*
		for (int i = 0;i < 5; i++) {
			std::cout << filter[i] << std::endl;
		}
		*/
		
		bool found = this->data.callIncludingDefault(filter, [keyStroke, this](SubHook subHook) {subHook.run(keyStroke, this->out);});

		if (!found) {
			this->out(keyStroke);
		}
	}
}
