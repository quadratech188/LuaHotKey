#pragma once

#include "lua.hpp"

#if defined(LUA_VERSION_NUM_) && LUA_VERSION_NUM < 502
	#define luaL_setfuncs(L, l, nup) luaL_register(L, NULL, l, nup)
	#define lua_rawlen(L, idx) lua_objlen(L, idx)
#endif

#define LUA_NEWUSERDATA(type, L) (type*)lua_newuserdata(L, sizeof(type))
#define LUA_CHECKUSERDATA(type, L, index, typeName) (type*)luaL_checkudata(L, index, typeName)
