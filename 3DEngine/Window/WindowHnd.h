#pragma once

#include <string>

#include "Logger.h"

#include "Event/EventDispatcher.h"

#include "Math/Vec2d.h"	

struct WindowSettings {
	int width = 500, height = 500;
	bool resizable = true, visible = true, decorated = true,
		focused = true, autoIconify = false, floating = false,
		maximized = false, centerCursor = true,
		transparentFramebuffer = false, focusOnShow = true,
		scaleToMonitor = true;
};

enum class WindowAttrib : int {
	FOCUSED, ICONIFIED, MAXIMIZED, VISIBLE, RESIZABLE,
	DECORATED, AUTO_ICONIFY, FLOATING, TRANSPARENT_FRAMEBUFFER,
	FOCUS_ON_SHOW,
};

class WindowHnd {

public:
	WindowHnd(const std::string& title) {
		m_Title = title; 
	}

	virtual ~WindowHnd() = default;

	virtual bool InitializeWindow() = 0;
	virtual bool InitializeWindow(const WindowSettings& flags) = 0;
	virtual bool QueryCloseRequested() const = 0; 
	virtual void SwapBuffers() const = 0;

	// Window-Related Functions
	
	virtual void GetWindowSize(int* width, int* height) const = 0;

	virtual float GetAspectRatio() const = 0;

	virtual bool GetWindowAttrib(const WindowAttrib& attrib) const = 0;
	virtual void SetWindowAttrib(const WindowAttrib& attrib, bool state) = 0; 

	virtual void DestroyWindow() = 0; 

	// Mouse-Related Functions

	enum MouseButton {
		LEFT = 0,
		RIGHT = 1
	};

	virtual bool IsMouseBtnPressed(MouseButton btn) const = 0; 

	virtual void SetCursorCentered() = 0;
	virtual void SetCursorHidden(bool hidden) = 0;

	const Vec2d& GetLastMousePosition() const { return m_MousePosition; }
	void SetLastMousePosition(const Vec2d& newPosition) { m_MousePosition = newPosition; }

	EventDispatcher& GetEventDispatcher() {
		return m_EventDispatcher; 
	}

protected:
	std::string m_Title{};
	Vec2d m_MousePosition{}; 
	EventDispatcher m_EventDispatcher{}; 

};

