#pragma once
#include "Event/IEvent.h"

struct MouseMoveEvent : IEvent {
	MouseMoveEvent(double xPos, double yPos) : xPos(xPos), yPos(yPos) {}
	double xPos, yPos; 
};