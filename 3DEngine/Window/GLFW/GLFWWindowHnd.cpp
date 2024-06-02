#include "GLFWWindowHnd.h"

#include "GLFWWindowCore.h"

#include "Event/Input/KeyPressEvent.h"
#include "Event/Input/MouseMoveEvent.h"
#include "Event/Input/MouseScrollEvent.h"
#include "Event/Input/WindowFocusEvent.h"
#include "Event/Input/WindowResizeEvent.h"

GLFWWindowHnd::GLFWWindowHnd(const std::string& title) : WindowHnd(title) {
	m_WindowPtr = nullptr; 
}

GLFWWindowHnd::~GLFWWindowHnd() {
	DestroyWindow();
}

bool GLFWWindowHnd::InitializeWindow() {
	return InitializeWindow(WindowSettings{});
}

bool GLFWWindowHnd::InitializeWindow(const WindowSettings& settings) {
	// set window creation hints
	glfwWindowHint(GLFW_RESIZABLE, settings.resizable);
	glfwWindowHint(GLFW_VISIBLE, settings.visible);
	glfwWindowHint(GLFW_DECORATED, settings.decorated);
	glfwWindowHint(GLFW_FOCUSED, settings.focused);
	glfwWindowHint(GLFW_AUTO_ICONIFY, settings.autoIconify);
	glfwWindowHint(GLFW_FLOATING, settings.floating);
	glfwWindowHint(GLFW_MAXIMIZED, settings.maximized);
	glfwWindowHint(GLFW_CENTER_CURSOR, settings.centerCursor);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, settings.transparentFramebuffer);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, settings.focusOnShow);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, settings.scaleToMonitor); 
	// create glfw window ptr
	m_WindowPtr = glfwCreateWindow(settings.width, settings.height, 
		m_Title.c_str(),
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

bool GLFWWindowHnd::GetWindowAttrib(const WindowAttrib& attrib) const {
	const auto glfwAttrib = Window::ParseWindowAttrib(attrib);
	if (glfwAttrib == -1) return false;
	return glfwGetWindowAttrib(m_WindowPtr, glfwAttrib); 
}

void GLFWWindowHnd::SetWindowAttrib(const WindowAttrib& attrib, bool state) {
	const auto glfwAttrib = Window::ParseWindowAttrib(attrib);
	if (glfwAttrib == -1) return; 
	glfwSetWindowAttrib(m_WindowPtr, glfwAttrib, 
		state ? GLFW_TRUE : GLFW_FALSE);
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

void GLFWWindowHnd::OnMouseMove(GLFWwindow* window, double xPos, double yPos) {
	auto* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	const MouseMoveEvent _event{ xPos, yPos };
	windowHnd->GetEventDispatcher().Dispatch<MouseMoveEvent>(_event); 
	windowHnd->SetLastMousePosition({xPos, yPos}); 
}

void GLFWWindowHnd::OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	auto& windowCore = GLFWWindowCore::Instance(); 
	const KeyPressEvent _event{ windowCore.ParseKeyCode(key),
		windowCore.ParseKeyAction(action) };
	windowHnd->GetEventDispatcher().Dispatch<KeyPressEvent>(_event); 
}

void GLFWWindowHnd::OnWindowResize(GLFWwindow* window, int width, int height) {
	auto* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	const WindowResizeEvent _event{ width, height };
	windowHnd->GetEventDispatcher().Dispatch<WindowResizeEvent>(_event); 
}

void GLFWWindowHnd::OnWindowFocus(GLFWwindow* window, int focused) {
	auto* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	const WindowFocusEvent _event{ static_cast<bool>(focused) };
	windowHnd->GetEventDispatcher().Dispatch<WindowFocusEvent>(_event); 
}

void GLFWWindowHnd::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	auto* windowHnd = static_cast<GLFWWindowHnd*>(glfwGetWindowUserPointer(window));
	const ScrollDirection direction = static_cast<bool>(yoffset) ? UP : DOWN;
	const MouseScrollEvent _event{ direction };
	windowHnd->GetEventDispatcher().Dispatch<MouseScrollEvent>(_event); 
}