#pragma once

#include <functional>
#include <memory>

#include "AttributeTree.h"
#include "KeyboardSubHook.h"

using namespace KeyboardSubHook;

namespace LayerNS {
	struct Layer {
		AttributeTree<SubHook> data;
		std::function<void(KeyStrokes)> out;
		void run(KeyStrokes keyStrokes);
	};

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
