#pragma once

#include "Event/Input/KeyPressEvent.h"

class IWindowCore {

public:
	virtual bool InitializeCore() = 0;
	virtual void ShutdownCore() = 0;

	virtual void PollEvents() = 0;

	virtual Key ParseKeyCode(int key) = 0;
	virtual KeyAction ParseKeyAction(int action) = 0;
};
