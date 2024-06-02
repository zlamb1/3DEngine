#pragma once

#include "Window/IWindowCore.h"

class GLFWWindowCore: public IWindowCore {

public:
	static GLFWWindowCore& Instance() {
		static GLFWWindowCore windowCore{};
		return windowCore; 
	}

	bool InitializeCore() override;
	void ShutdownCore() override;

	void PollEvents() override;

	Key ParseKeyCode(int key) override;
	KeyAction ParseKeyAction(int action) override; 

private:
	GLFWWindowCore() = default;
	~GLFWWindowCore() = default; 

};