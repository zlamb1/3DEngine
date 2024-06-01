#pragma once
#include "Event/IEvent.h"

struct WindowFocusEvent : IEvent {
	WindowFocusEvent(bool focused) : focused(focused) {}
	bool focused;
};