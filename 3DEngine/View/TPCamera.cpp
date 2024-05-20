#include "TPCamera.h"

#include "Logger.h"

constexpr float MOUSE_SENS = 0.02f; 

glm::mat4 TPCamera::CreateViewMatrix() const {
	return glm::lookAt(CameraUtility::VectorInUnitSphere(m_Position, m_Rotation.x, m_Rotation.y) * m_Zoom,
		m_Position, CameraUtility::UP_VECTOR);
}

void TPCamera::ProcessMouseMove(const WindowHnd& window, double xpos, double ypos) {
	if (window.IsMouseBtnPressed(WindowHnd::LEFT)) {
		double lastXPos, lastYPos;
		window.GetLastMousePos(&lastXPos, &lastYPos);
		const double dx = xpos - lastXPos, dy = ypos - lastYPos;
		m_Rotation += glm::vec3(-dx, dy, 0) * MOUSE_SENS;
		ClampPitch();
	}
}

void TPCamera::ProcessMouseScroll(const WindowHnd& window, double xoffset, double yoffset) {
	constexpr float ZOOM_SPEED = 1.25f;
	if (yoffset != 1.0) {
		m_Zoom *= ZOOM_SPEED;
	} else {
		m_Zoom /= ZOOM_SPEED;
	}
}