#pragma once

#include <windows.h>

#include "Stroke.h"

struct KeyStroke {
	DWORD vkCode;
	DWORD scanCode;
	Stroke stroke;
	int modifiers;
	bool autorepeat;

	KeyStroke():
		vkCode(0), scanCode(0), stroke(Stroke::PRESS), autorepeat(false) {}

	KeyStroke(DWORD vkCode, DWORD scanCode, Stroke stroke, int modifiers, bool autorepeat):
		vkCode(vkCode), scanCode(scanCode), stroke(stroke), modifiers(modifiers), autorepeat(autorepeat) {}

	KeyStroke(WPARAM wParam, LPARAM lParam);

	std::array<int, 5> toFilter();

	void resolve(KeyStroke& context);

	bool operator==(const KeyStroke& other) const {
		return (this->vkCode == other.vkCode
			 && this->scanCode == other.scanCode
			 && this->stroke == other.stroke);
	}
};
