#pragma once

#include "lua.hpp"
#include <string_view>

#if defined(LUA_VERSION_NUM_) && LUA_VERSION_NUM < 502
	#define luaL_setfuncs(L, l, nup) luaL_register(L, NULL, l, nup)
	#define lua_rawlen(L, idx) lua_objlen(L, idx)
#endif

template <typename T>
inline T* luaExt_checkudata(lua_State* L, const int index, const std::string_view metatableName) {
	return (T*)luaL_checkudata(L, index, metatableName.data());
}
template <typename T>
inline T* luaExt_newuserdata(lua_State* L) {
	return (T*)lua_newuserdata(L, sizeof(T));
}
template <typename T, typename... Args>
inline T* luaExt_emplaceuserdata(lua_State* L, Args&&... args) {
	T* result = luaExt_newuserdata<T>(L);
	new (result) T(std::forward<Args>(args)...);
	return result;
}
