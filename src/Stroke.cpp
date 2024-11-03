#include "Stroke.h"

#include <stdexcept>
#include <string>

#include "KeyboardHook.h"

Stroke::Stroke(lua_State* L, int index) {
	std::string name = luaL_checkstring(L, index);

	if (name == "mirror") {
		this->value = MIRROR;
	}
	else if (name == "release") {
		this->value = RELEASE;
	}
	else {
		this->value = PRESS;
	}
}

Stroke::operator std::string() const {
	switch (this->value) {
		case PRESS:
			return "press";
		case RELEASE:
			return "release";
		case MIRROR:
			return "mirror";
		default:
			throw std::runtime_error("Invalid stroke value");
	}
}

Stroke::operator int() const {
	return this->value;
}

bool Stroke::isRelease() const{
	switch(this->value) {
		case PRESS:
			return false;
		case RELEASE:
			return true;
		case MIRROR:
			return KeyboardHook::keyStroke.stroke == RELEASE;
		default:
			throw std::runtime_error("Invalid stroke value");
	}
}

void Stroke::resolve(Stroke context) {
	if (this->value == MIRROR) {
		this->value = context.value;
	}
}
