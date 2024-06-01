#include "Player.h"

#include <GLFW/glfw3.h>

Player::Player(std::unique_ptr<Camera> camera) : m_Camera(std::move(camera)) {
	
}

void Player::OnFrame(const std::vector<bool>& keyBuffer, const FrameTime& frameTime) {
	m_Velocity *= m_ExpFriction; 

	const glm::vec3 forwardDir = normalize(
		glm::vec3{ sin(m_Camera->Rotation().x),
			0.0f,
			cos(m_Camera->Rotation().x)});
	const glm::vec3 rightDir = cross(forwardDir, CameraUtility::UP_VECTOR);
	const auto dt = static_cast<float>(frameTime.DeltaTime()); 
	float calcMovementSpeed = m_MovementSpeed;

	if (keyBuffer.size() > GLFW_KEY_LEFT_SHIFT && keyBuffer[GLFW_KEY_LEFT_SHIFT])
		calcMovementSpeed *= 3.0f;
	if (keyBuffer.size() > GLFW_KEY_W && keyBuffer[GLFW_KEY_W])
		m_Velocity += forwardDir * calcMovementSpeed;
	if (keyBuffer.size() > GLFW_KEY_S && keyBuffer[GLFW_KEY_S])
		m_Velocity -= forwardDir * calcMovementSpeed;
	if (keyBuffer.size() > GLFW_KEY_D && keyBuffer[GLFW_KEY_D])
		m_Velocity += rightDir * calcMovementSpeed;
	if (keyBuffer.size() > GLFW_KEY_A && keyBuffer[GLFW_KEY_A])
		m_Velocity -= rightDir * calcMovementSpeed;
	if (keyBuffer.size() > GLFW_KEY_SPACE && keyBuffer[GLFW_KEY_SPACE])
		m_Velocity += CameraUtility::UP_VECTOR * calcMovementSpeed;
	if (keyBuffer.size() > GLFW_KEY_LEFT_CONTROL && keyBuffer[GLFW_KEY_LEFT_CONTROL])
		m_Velocity -= CameraUtility::UP_VECTOR * calcMovementSpeed;

	m_Camera->Position() += m_Velocity * dt; 
}

void Player::OnMouseMove(const WindowHnd& window, double xpos, double ypos) const {
	m_Camera->ProcessMouseMove(window, xpos, ypos); 
}

void Player::OnMouseScroll(const WindowHnd& window, double xoffset, double yoffset) const {
	m_Camera->ProcessMouseScroll(window, xoffset, yoffset); 
}

float& Player::MouseSensitivity() const {
	return m_Camera->MouseSensitivity();
}

glm::mat4 Player::CreateViewMatrix() const {
	return m_Camera->CreateViewMatrix(); 
}