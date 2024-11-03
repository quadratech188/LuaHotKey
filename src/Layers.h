#pragma once

#include "KeyStroke.h"

namespace Layers {
	void open(lua_State* L);

	int set(lua_State* L);

	void run(KeyStroke keyStroke);
}
