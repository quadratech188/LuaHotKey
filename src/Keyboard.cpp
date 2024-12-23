#include <array>

#include <windows.h>

class Keyboard {
public:
	Keyboard() {
		GetKeyboardState(data.data());
	}

	Keyboard(WPARAM wParam, LPARAM lParam) {
		GetKeyboardState(data.data());
	}

private:
	std::array<BYTE, 256> data;
};
