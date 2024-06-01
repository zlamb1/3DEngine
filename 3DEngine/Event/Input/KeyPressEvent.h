#pragma once
#include "Event/IEvent.h"

struct KeyPressEvent : IEvent {
	KeyPressEvent(int button, int action) : button(button), action(action) {}
	int button, action; 
};