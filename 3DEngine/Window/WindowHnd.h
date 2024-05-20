#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Logger.h"

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

	virtual void GetLastMousePos(double* xpos, double* ypos) const {
		if (xpos && ypos) {
			*xpos = m_LastMouseX;
			*ypos = m_LastMouseY;
		} else {
			LOG_WARN("Attempted to Retrieve Last Mouse Position with Nullptrs");
		}
	}

	// Hook-Related Functions

	void HookMouseMove(const Window::DPosCallback& callback) {
		m_MouseMoveCallbacks.emplace_back(callback); 
	}

	void HookKeyPress(const Window::KeyCallback& callback) {
		m_KeyPressCallbacks.emplace_back(callback);
	}

	void HookWindowResize(const Window::ISizeCallback& callback) {
		m_WindowResizeCallbacks.emplace_back(callback);
	}

	void HookWindowFocus(const Window::FocusCallback& callback) {
		m_WindowFocusCallbacks.emplace_back(callback); 
	}

	void HookMouseScroll(const Window::ScrollCallback& callback) {
		m_MouseScrollCallbacks.emplace_back(callback);
	}

protected:
	std::string m_Title;
	std::vector<Window::DPosCallback> m_MouseMoveCallbacks{};
	std::vector<Window::KeyCallback> m_KeyPressCallbacks{};
	std::vector<Window::ISizeCallback> m_WindowResizeCallbacks{};
	std::vector<Window::FocusCallback> m_WindowFocusCallbacks{};
	std::vector<Window::ScrollCallback> m_MouseScrollCallbacks{};

	double m_LastMouseX = 0, m_LastMouseY = 0;

};

