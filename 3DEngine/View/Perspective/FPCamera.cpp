#include "FPCamera.h"

void FPCamera::OnMouseMove(const WindowHnd& window, const Vec2d& position) {
	int width, height;
	window.GetWindowSize(&width, &height);
	const double dx = position.x - (width / 2.0), dy = position.y - (height / 2.0);
	m_Rotation += glm::vec3(-dx, -dy, 0) * m_MouseSens;
	ClampPitch();
	UpdateViewModel(); 
}

void FPCamera::UpdateViewModel() {
	m_ViewMatrix = lookAt(m_Position,
		m_Position + glm::vec3{ sin(m_Rotation.x) * cos(m_Rotation.y),
			sin(m_Rotation.y),
			cos(m_Rotation.x) * cos(m_Rotation.y) },
		CameraUtility::UP_VECTOR);
	// update proj
	m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix; 
}
