#pragma once

#include "KeyStroke.h"
#include <stack>

struct StackMember {
	KeyStroke keyStroke;
	int index;
	void run();
}
