#include "Layers.h"

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "Keyboard.h"
#include "KeyboardHook.h"
#include "Layer.h"

using namespace LayerNS;
using namespace KeyboardSubHook;

namespace Layers {

	std::shared_ptr<Layer> firstLayer;

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

		std::shared_ptr<Layer> layer, nextLayer;

		lua_rawgeti(L, 1, 1); // First layer
		
		layer = LayerNS::get(L, -1)->layer;

		firstLayer = layer;

		for (int i = 0; i < length - 1; i++) {
			lua_rawgeti(L, 1, i + 1 + 1); // We get the i+1-th element, and lua indices start at 1

			nextLayer = LayerNS::get(L, -1)->layer;

			layer->out = [nextLayer](KeyStroke keyStroke) {nextLayer->run(keyStroke);};

			layer = nextLayer;
		}

		// The final layer sends the processed keystrokes
		
		layer->out = [](KeyStroke keyStroke) {
			if (!KeyboardHook::processed) return; // Nothing matched, we're going to send the original keystroke so don't do anything here

			std::array<KeyStroke, 1> temp = {keyStroke};
			Keyboard::sendKeyStrokes(temp);
		};


		return 0;
	}

	void run(KeyStroke keyStroke) {
		if (firstLayer == nullptr) return;

		firstLayer->run(keyStroke);
	}
}
