#pragma once

#include <memory>

#include "AttributeTree.h"
#include "KeyboardSubHook.h"
#include "LuaHeader.h"

using namespace KeyboardSubHook;

namespace LayerNS {
	typedef AttributeTree<SubHook> Layer;

	struct LayerUdata {
		std::shared_ptr<Layer> layer;
		LayerUdata() {
			layer = std::make_shared<Layer>();
		}
	};

	void open(lua_State* L);

	int newUserdata(lua_State* L);

	int reg(lua_State* L);

	LayerUdata* get(lua_State* L, int index);
}
