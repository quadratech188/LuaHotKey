#include "Keyboard.h"
#include <functional>

class Layer {
public:
	void run(Keyboard& keyboard) {
	}
private:
	std::function<void(Keyboard&)> out;
};
