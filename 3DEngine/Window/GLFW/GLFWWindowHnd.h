#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../WindowHnd.h"

class GLFWWindowHnd: public WindowHnd {

public:
	GLFWWindowHnd(const std::string& title);
	~GLFWWindowHnd() override;

	bool InitializeWindow() override;
	bool InitializeWindow(const Window::InitFlags& flags) override;
	bool QueryCloseRequested() const override;
	void SwapBuffers() const override;

	void GetWindowSize(int* width, int* height) const override;
	float GetAspectRatio() const override;
	bool IsFocused() const override; 

	void DestroyWindow() final;

	bool IsMouseBtnPressed(MouseButton btn) const override;

	void SetCursorCentered() override;
	void SetCursorHidden(bool hidden) override;

	// Non-Inherited Functions

	void SetLastMousePosition(double xpos, double ypos); 

private:
	GLFWwindow* m_WindowPtr;

	// GLFW callbacks
	static void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
	static void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods); 
	static void OnWindowResize(GLFWwindow* window, int width, int height);
	static void OnWindowFocus(GLFWwindow* window, int focused);
	static void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset); 

};