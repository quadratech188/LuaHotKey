#include "Flags.h"
#include <stdexcept>

static bool boolFromLua(lua_State* L, const char* index, int tableIndex, bool defaultBool) {
	lua_getfield(L, tableIndex, index);
	if (!lua_isboolean(L, -1))
		return defaultBool;

	bool result = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return result;
}

Flags::Flags() {
	block = true;
	blockAutoRepeat = true;
}

Flags::Flags(lua_State* L, int index) {
	this->block = boolFromLua(L, "block", index, true);
	this->blockAutoRepeat = boolFromLua(L, "blockAutoRepeat", index, this->block);
}
