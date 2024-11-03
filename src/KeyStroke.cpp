#include "KeyStroke.h"

#include <array>

#include "KeyboardHook.h"
#include "Modifiers.h"

KeyStroke KeyStroke::fromCurrentState(WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT strokeInfo = *(KBDLLHOOKSTRUCT*)lParam;

	KeyStroke result;

	switch(wParam) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		result.stroke = Stroke::PRESS;
		break;
		
		case WM_KEYUP:
		case WM_SYSKEYUP:
		result.stroke = Stroke::RELEASE;
	}

	result.vkCode = strokeInfo.vkCode;
	result.scanCode = strokeInfo.scanCode;
	
	result.autorepeat = KeyboardHook::prevKeyStroke.vkCode == result.vkCode
		             && KeyboardHook::prevKeyStroke.scanCode == result.scanCode
		             && KeyboardHook::prevKeyStroke.stroke == result.stroke;

	result.modifiers = Modifiers::createFromKeyboardState();

	return result;
}

void KeyStroke::resolve(KeyStroke context) {
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
