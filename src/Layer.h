#pragma once

#include "Keyboard.h"

class Layer {
public:
	void run(Keyboard&);
	Layer* next;
};
