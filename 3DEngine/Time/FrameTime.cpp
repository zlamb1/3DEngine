#include "FrameTime.h"

#include <GLFW/glfw3.h>

// Potentially refactor this to not use GLFW

void FrameTime::OnFrame() {
	m_LastFrameTime = glfwGetTime();
}

double FrameTime::DeltaTime() const {
	return glfwGetTime() - m_LastFrameTime; 
}
