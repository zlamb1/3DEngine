#include "GLFWWindowHnd.h"

GLFWWindowHnd::GLFWWindowHnd(const std::string& title) : WindowHnd(title) {
	m_WindowPtr = nullptr; 
}

GLFWWindowHnd::~GLFWWindowHnd() {
	DestroyWindow();
}

bool GLFWWindowHnd::InitializeWindow() {
	return InitializeWindow(Window::InitFlags{});
}

bool GLFWWindowHnd::InitializeWindow(const Window::InitFlags& flags) {
	// set window creation hints
	glfwWindowHint(GLFW_MAXIMIZED, flags.m_Maximized);
	// create glfw window ptr
	m_WindowPtr = glfwCreateWindow(flags.m_Width, flags.m_Height, m_Title.c_str(), 
		nullptr, nullptr);
	// check ptr
	if (!m_WindowPtr) return false;
	// set user pointer
	glfwSetWindowUserPointer(m_WindowPtr, this);
	// set static callbacks
	glfwSetCursorPosCallback(m_WindowPtr, OnMouseMove);
	glfwSetKeyCallback(m_WindowPtr, OnKeyPress);
	glfwSetWindowSizeCallback(m_WindowPtr, OnWindowResize);
	glfwSetWindowFocusCallback(m_WindowPtr, OnWindowFocus);
	glfwSetScrollCallback(m_WindowPtr, OnMouseScroll);
	// make GL context current
	glfwMakeContextCurrent(m_WindowPtr);
	return true;
}


bool GLFWWindowHnd::QueryCloseRequested() const {
	return glfwWindowShouldClose(m_WindowPtr);
}

void GLFWWindowHnd::SwapBuffers() const {
	glfwSwapBuffers(m_WindowPtr);
}

void GLFWWindowHnd::GetWindowSize(int* width, int* height) const {
	glfwGetWindowSize(m_WindowPtr, width, height);
}

float GLFWWindowHnd::GetAspectRatio() const {
	int width, height;
	GetWindowSize(&width, &height);
	return static_cast<float>(width) / static_cast<float>(height); 
}

bool GLFWWindowHnd::IsFocused() const {
	return glfwGetWindowAttrib(m_WindowPtr, GLFW_FOCUSED);
}

void GLFWWindowHnd::DestroyWindow() {
	if (m_WindowPtr) {
		glfwDestroyWindow(m_WindowPtr);
		m_WindowPtr = nullptr; 
	}
}

bool GLFWWindowHnd::IsMouseBtnPressed(MouseButton btn) const {
	return glfwGetMouseButton(m_WindowPtr, btn == MouseButton::LEFT ? 
		GLFW_MOUSE_BUTTON_LEFT : GLFW_MOUSE_BUTTON_RIGHT);
}

void GLFWWindowHnd::SetCursorCentered() {
	int width, height;
	GetWindowSize(&width, &height);
	glfwSetCursorPos(m_WindowPtr, width / 2.0, height / 2.0);
}

void GLFWWindowHnd::SetCursorHidden(bool hidden) {
	glfwSetInputMode(m_WindowPtr, GLFW_CURSOR, hidden ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
}

void GLFWWindowHnd::SetLastMousePosition(double xpos, double ypos) {
	m_LastMouseX = xpos;
	m_LastMouseY = ypos; 
}

void GLFWWindowHnd::OnMouseMove(GLFWwindow* window, double xpos, double ypos) {
	GLFWWindowHnd* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	for (auto& f : windowHnd->m_MouseMoveCallbacks) {
		f(xpos, ypos);
	}

	windowHnd->SetLastMousePosition(xpos, ypos); 
}

void GLFWWindowHnd::OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	const GLFWWindowHnd* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	for (auto& f : windowHnd->m_KeyPressCallbacks) {
		f(key, action); 
	}
}

void GLFWWindowHnd::OnWindowResize(GLFWwindow* window, int width, int height) {
	const GLFWWindowHnd* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	for (auto& f : windowHnd->m_WindowResizeCallbacks) {
		f(width, height);
	}
}

void GLFWWindowHnd::OnWindowFocus(GLFWwindow* window, int focused) {
	const GLFWWindowHnd* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	for (auto& f : windowHnd->m_WindowFocusCallbacks) {
		f(focused); 
	}
}

void GLFWWindowHnd::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	const GLFWWindowHnd* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	for (auto& f : windowHnd->m_MouseScrollCallbacks) {
		f(xoffset, yoffset); 
	}
}