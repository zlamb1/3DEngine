#include "FPCamera.h"

#include "GLFW/glfw3.h"

glm::mat4 FPCamera::CreateViewMatrix() const {
	return lookAt(m_Position, 
		m_Position + glm::vec3{sin(m_Rotation.x) * cos(m_Rotation.y),
			sin(m_Rotation.y),
			cos(m_Rotation.x) * cos(m_Rotation.y) },
		CameraUtility::UP_VECTOR);
}

void FPCamera::ProcessMouseMove(const WindowHnd& window, double xpos, double ypos) {
	int width, height;
	window.GetWindowSize(&width, &height);
	const double dx = xpos - (width / 2.0), dy = ypos - (height / 2.0);
	m_Rotation += glm::vec3(-dx, -dy, 0) * m_MouseSens;
	ClampPitch();
}
