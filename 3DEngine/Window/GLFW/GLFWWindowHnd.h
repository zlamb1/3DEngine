#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Window/WindowHnd.h"

namespace Window {
	static int ParseWindowAttrib(WindowAttrib attrib) {
		switch (attrib) {
			case WindowAttrib::RESIZABLE:
				return GLFW_RESIZABLE;
			case WindowAttrib::VISIBLE:
				return GLFW_VISIBLE;
			case WindowAttrib::DECORATED:
				return GLFW_DECORATED; 
			case WindowAttrib::FOCUSED:
				return GLFW_FOCUSED; 
			case WindowAttrib::AUTO_ICONIFY:
				return GLFW_AUTO_ICONIFY; 
			case WindowAttrib::FLOATING:
				return GLFW_FLOATING;
			case WindowAttrib::MAXIMIZED:
				return GLFW_MAXIMIZED; 
			case WindowAttrib::TRANSPARENT_FRAMEBUFFER:
				return GLFW_TRANSPARENT_FRAMEBUFFER; 
			case WindowAttrib::FOCUS_ON_SHOW:
				return GLFW_FOCUS_ON_SHOW; 
			case WindowAttrib::ICONIFIED:
				return GLFW_ICONIFIED;
		}

		return -1; 
	}
}

class GLFWWindowHnd: public WindowHnd {

public:
	GLFWWindowHnd(const std::string& title);
	~GLFWWindowHnd() override;

	bool InitializeWindow() override;
	bool InitializeWindow(const WindowSettings& settings) override;
	bool QueryCloseRequested() const override;
	void SwapBuffers() const override;

	void GetWindowSize(int* width, int* height) const override;

	float GetAspectRatio() const override;

	bool GetWindowAttrib(const WindowAttrib& attrib) const override;
	void SetWindowAttrib(const WindowAttrib& attrib, bool state) override;

	void DestroyWindow() final;

	bool IsMouseBtnPressed(MouseButton btn) const override;

	void SetCursorCentered() override;
	void SetCursorHidden(bool hidden) override;

private:
	GLFWwindow* m_WindowPtr;

	// GLFW callbacks
	static void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
	static void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods); 
	static void OnWindowResize(GLFWwindow* window, int width, int height);
	static void OnWindowFocus(GLFWwindow* window, int focused);
	static void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset); 

};