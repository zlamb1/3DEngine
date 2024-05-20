#include "FPCamera.h"

#include "GLFW/glfw3.h"

constexpr float MOVEMENT_SPEED = 0.002f;
constexpr float MOUSE_SENS = 0.003f;

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
	m_Rotation += glm::vec3(-dx, -dy, 0) * MOUSE_SENS;
	ClampPitch();
}

void FPCamera::ProcessKeyInput(const WindowHnd& window, const std::vector<bool>& keyBuffer) {
	const glm::vec3 forwardDir = normalize(glm::vec3{ sin(m_Rotation.x), 0.0f, cos(m_Rotation.x) });
	const glm::vec3 rightDir = cross(forwardDir, CameraUtility::UP_VECTOR);
	if (keyBuffer.size() > GLFW_KEY_W && keyBuffer[GLFW_KEY_W])
		m_Position += forwardDir * MOVEMENT_SPEED;
	if (keyBuffer.size() > GLFW_KEY_S && keyBuffer[GLFW_KEY_S])
		m_Position -= forwardDir * MOVEMENT_SPEED;
	if (keyBuffer.size() > GLFW_KEY_D && keyBuffer[GLFW_KEY_D])
		m_Position += rightDir * MOVEMENT_SPEED;
	if (keyBuffer.size() > GLFW_KEY_A && keyBuffer[GLFW_KEY_A])
		m_Position -= rightDir * MOVEMENT_SPEED;
	if (keyBuffer.size() > GLFW_KEY_SPACE && keyBuffer[GLFW_KEY_SPACE])
		m_Position += CameraUtility::UP_VECTOR * MOVEMENT_SPEED;
	if (keyBuffer.size() > GLFW_KEY_LEFT_CONTROL && keyBuffer[GLFW_KEY_LEFT_CONTROL])
		m_Position -= CameraUtility::UP_VECTOR * MOVEMENT_SPEED; 
}
