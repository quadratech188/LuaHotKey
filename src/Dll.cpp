#include "Dll.h"

#include <windows.h>

#include "KeyboardHook.h"
#include "LayerLua.h"
#include "LuaHeader.h"

extern "C" __declspec(dllexport) int luaopen_lhk_core(lua_State* L) {
	LuaHotKey::open(L); // Creates the module
	
	LayerLua::open(L);
	return 1;
}

namespace LuaHotKey {
	lua_State* L;
	Layer* first;
	

	const luaL_Reg luaFunctions[] = {
		{"start", start},
		{"stop", stop},
		{"begin", begin},
		{NULL, NULL}
	};

	void open(lua_State* L) {
		LuaHotKey::L = L;
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);
	}

	int start(lua_State* L) {
		KeyboardHook::hook();

		MSG msg;
		while(GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return 0;
	}

	int stop(lua_State* L) {
		KeyboardHook::unHook();
		PostQuitMessage(0);
		return 0;
	}

	int begin(lua_State* L) {
		first = LayerLua::get(L, 1);
		return 0;
	}
}
