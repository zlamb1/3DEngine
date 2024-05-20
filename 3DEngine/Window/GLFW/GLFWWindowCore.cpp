#include "GLFWWindowCore.h"

#include <GLFW/glfw3.h>

bool GLFWWindowCore::InitializeCore() {
	return glfwInit();
}

void GLFWWindowCore::ShutdownCore() {
	glfwTerminate();
}

void GLFWWindowCore::PollEvents() {
	glfwPollEvents();
}
