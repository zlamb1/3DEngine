#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Logger.h"

#include "Event/EventDispatcher.h"

namespace Window {
	struct InitFlags {
		bool m_Maximized = false;
		int m_Width = 500;
		int m_Height = 500;
	};

	typedef std::function<void(double, double)> DPosCallback;
	typedef std::function<void(int, int)> ISizeCallback;

	typedef std::function<void(int, int)> KeyCallback;
	typedef std::function<void(bool)> FocusCallback;
	typedef std::function<void(double, double)> ScrollCallback;
}

class WindowHnd {

public:
	WindowHnd(const std::string& title) {
		m_Title = title; 
	}

	virtual ~WindowHnd() = default;

	virtual bool InitializeWindow() = 0;
	virtual bool InitializeWindow(const Window::InitFlags& flags) = 0;
	virtual bool QueryCloseRequested() const = 0; 
	virtual void SwapBuffers() const = 0;

	// Window-Related Functions
	
	virtual void GetWindowSize(int* width, int* height) const = 0;
	virtual float GetAspectRatio() const = 0;
	virtual bool IsFocused() const = 0;

	virtual void DestroyWindow() = 0; 

	// Mouse-Related Functions

	enum MouseButton {
		LEFT = 0,
		RIGHT = 1
	};

	virtual bool IsMouseBtnPressed(MouseButton btn) const = 0; 

	virtual void SetCursorCentered() = 0;
	virtual void SetCursorHidden(bool hidden) = 0;

	virtual void GetLastMousePos(double* xPos, double* yPos) const {
		if (xPos && yPos) {
			*xPos = m_LastMouseX;
			*yPos = m_LastMouseY;
		} else {
			LOG_WARN("Cannot Store Last Mouse Position to Nullptr")
		}
	}

	EventDispatcher& GetEventDispatcher() {
		return m_EventDispatcher; 
	}

protected:
	std::string m_Title{};
	double m_LastMouseX = 0, m_LastMouseY = 0;
	EventDispatcher m_EventDispatcher{}; 

};

