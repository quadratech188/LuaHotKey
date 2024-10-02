#include <string>
#include <format>
#include <windows.h>

#include "LuaHeader.h"
#include "KeyStroke.h"
#include "KeyStrokeLua.h"
#include "Definitions.h"

namespace KeyStrokeLua {
	const char* userdataName = "lhk.KeyStroke";
	const char* metatableName = "lhk.KeyStroke";

	const luaL_Reg luaFunctions[] = {
		{"new", newUserdata},
		{NULL, NULL}
	};

	const luaL_Reg luaMembers[] = {
		{"__newindex", set},
		{"__index", get},
		{"__tostring", toString},
		{NULL, NULL}
	};

	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);
		lua_setfield(L, -2, "KeyStroke");

		luaL_newmetatable(L, metatableName);
		luaL_setfuncs(L, luaMembers, 0);
		lua_pop(L, 1); // Pop metatable reference
	}

	KeyStroke get(lua_State* L, int index) {
		return *LUA_CHECKUSERDATA(KeyStroke, L, index, metatableName);
	}

	int set(lua_State* L) {
		KeyStroke* keyStroke = LUA_CHECKUSERDATA(KeyStroke, L, 1, metatableName);
		std::string index = std::string(luaL_checkstring(L, 2));

		if (index == "vkCode") {
			keyStroke->vkCode = lua_tointeger(L, 3);
		}
		else if (index == "scanCode") {
			keyStroke->scanCode = lua_tointeger(L, 3);
		}
		else if (index == "stroke") {
			keyStroke->stroke = Stroke(L, 3);
		}
		else {
			luaL_argcheck(L, false, 2, "invalid index");
		}
		return 0;
	}


	int get(lua_State* L) {
		KeyStroke* keyStroke = LUA_CHECKUSERDATA(KeyStroke, L, 1, metatableName);
		std::string index = std::string(luaL_checkstring(L, 2));

		if (index == "vkCode") {
			lua_pushinteger(L, keyStroke->vkCode);
		}
		else if (index == "scanCode") {
			lua_pushinteger(L, keyStroke->scanCode);
		}
		else if (index == "stroke") {
			lua_pushstring(L, static_cast<std::string>(keyStroke->stroke).c_str());
		}
		else {
			luaL_argcheck(L, false, 2, "invalid index");
		}
		return 1;
	}

	int toString(lua_State* L) {
		KeyStroke* keyStroke = LUA_CHECKUSERDATA(KeyStroke, L, 1, metatableName);

		std::string data = std::format("vkCode: {}, scanCode: {}, stroke: {}",
				keyStroke->vkCode != 0? std::to_string(keyStroke->vkCode): "Unspecified",
				keyStroke->scanCode != 0? std::to_string(keyStroke->scanCode): "Unspecified",
				static_cast<std::string>(keyStroke->stroke));

		lua_pushstring(L, data.c_str());

		return 1;
	}

	int newUserdata(lua_State* L) {
		KeyStroke keyStroke;

		int numArgs = lua_gettop(L);
		
		keyStroke.vkCode = (numArgs >= 1 && !lua_isnil(L, 1))? lua_tointeger(L, 1): 0;

		keyStroke.scanCode = (numArgs >= 2 && !lua_isnil(L, 2))? lua_tointeger(L, 2): 0;

		if (numArgs >= 3) {
			keyStroke.stroke = Stroke(L, 3);
		}
		else {
			keyStroke.stroke = Stroke();
		}

		KeyStroke* userdataPtr = LUA_NEWUSERDATA(KeyStroke, L);

		*userdataPtr = keyStroke;

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;
	}

	int newUserdata(lua_State* L, WPARAM wParam, LPARAM lParam) {
		KeyStroke* userdataPtr = LUA_NEWUSERDATA(KeyStroke, L);

		*userdataPtr = KeyStroke(wParam, lParam);

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;

	}

	int newUserdata(lua_State* L, KeyStroke keyStroke) {
		*LUA_NEWUSERDATA(KeyStroke, L) = keyStroke;

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;
	}
}
