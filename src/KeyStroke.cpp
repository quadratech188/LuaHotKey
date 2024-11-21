#include "KeyStroke.h"

#include <array>

#include "Modifiers.h"
#include "Stroke.h"

KeyStroke::KeyStroke(WPARAM wParam, LPARAM lParam) {
	static KeyStroke prev;

	KBDLLHOOKSTRUCT strokeInfo = *(KBDLLHOOKSTRUCT*)lParam;

	switch(wParam) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		this->stroke = Stroke::PRESS;
		break;
		
		case WM_KEYUP:
		case WM_SYSKEYUP:
		this->stroke = Stroke::RELEASE;
	}

	this->vkCode = strokeInfo.vkCode;
	this->scanCode = strokeInfo.scanCode;
	
	this->autorepeat = this->vkCode == prev.vkCode
		&& this->scanCode == prev.scanCode
		&& this->stroke == prev.stroke;

	this->modifiers = Modifiers::fromKeyboardState();

	prev = *this;
}

void KeyStroke::resolve(KeyStroke& context) {
	this->autorepeat = context.autorepeat;
	this->modifiers = context.modifiers;
	this->stroke.resolve(context.stroke);
}

std::array<int, 5> KeyStroke::toFilter() {
	return {
		(int)this->vkCode,
		(int)this->scanCode,
		this->modifiers,
		this->autorepeat,
		this->stroke
	};
}
