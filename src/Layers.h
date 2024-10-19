#pragma once

#include <memory>
#include <span>
#include <vector>

#include "KeyStroke.h"
#include "Layer.h"
#include "LuaHeader.h"

using namespace LayerNS;

namespace Layers {
	extern std::vector<std::shared_ptr<Layer>> layers;

	void open(lua_State* L);

	int set(lua_State* L);

	void run(KeyStroke keyStroke);
}
