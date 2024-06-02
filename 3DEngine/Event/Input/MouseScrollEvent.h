#pragma once
#include "Event/IEvent.h"

enum ScrollDirection {
	UP, DOWN
};

struct MouseScrollEvent : IEvent {
	MouseScrollEvent(ScrollDirection direction) : direction(direction) {}
	ScrollDirection direction;
};