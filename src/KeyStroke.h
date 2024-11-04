#pragma once

#include <span>

#include <windows.h>

#include "Stroke.h"

struct KeyStroke {
	DWORD vkCode;
	DWORD scanCode;
	Stroke stroke;
	int modifiers;
	bool autorepeat;

	std::array<int, 5> toFilter();
	
	static KeyStroke fromCurrentState(WPARAM, LPARAM);

	void resolve(KeyStroke& context);

	bool operator==(const KeyStroke& other) const {
		return (this->vkCode == other.vkCode
			 && this->scanCode == other.scanCode
			 && this->stroke == other.stroke);
	}
};

typedef std::span<KeyStroke> KeyStrokes;
