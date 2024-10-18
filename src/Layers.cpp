#include "Layers.h"

#include <memory>
#include <vector>

#include "Layer.h"
#include "LuaHeader.h"

using namespace LayerNS;
using namespace KeyboardSubHook;

namespace Layers {

	std::vector<std::shared_ptr<Layer>> layers = std::vector<std::shared_ptr<Layer>>();

	const luaL_Reg luaFunctions[] = {
		{"set", set},
		{NULL, NULL}
	};
	
	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);

		lua_setfield(L, -2, "layers");
	}

	int set(lua_State* L) {
		luaL_argcheck(L, lua_istable(L, 1), 1, "Expected lhk.Layer table");

		int length = lua_rawlen(L, 1);

		layers.clear();

		layers.reserve(length);

		for (int i = 0; i < length; i++) {
			lua_rawgeti(L, 1, i + 1); // lua indices start at 1

			LayerUdata* userdataPtr = LayerNS::get(L, -1);

			layers.push_back(userdataPtr->layer);
		}
		return 0;
	}
}
