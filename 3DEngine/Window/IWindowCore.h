#pragma once

class IWindowCore {

public:
	virtual bool InitializeCore() = 0;
	virtual void ShutdownCore() = 0;

	virtual void PollEvents() = 0;
};