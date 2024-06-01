#pragma once
#include "Event/IEvent.h"

enum MouseScrollDirection {
	UP, DOWN
};

struct MouseScrollEvent : IEvent {
	MouseScrollEvent(MouseScrollDirection direction) : direction(direction) {}
	MouseScrollDirection direction;
};