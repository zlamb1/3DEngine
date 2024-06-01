#pragma once
#include "Event/IEvent.h"

struct WindowResizeEvent : IEvent {
	WindowResizeEvent(int width, int height) : width(width), height(height) {}
	int width, height;
};