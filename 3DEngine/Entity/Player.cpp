#include "Player.h"

Player::Player(Scope<Camera> camera) : m_Camera(std::move(camera))
{
}

void Player::OnFrame(const std::vector<KeyAction>& keyBuffer, const FrameTime& frameTime) {
	m_Velocity *= m_ExpFriction; 

	const glm::vec3 forwardDir = normalize(
		glm::vec3{ sin(m_Camera->GetRotation().x),
			0.0f,
			cos(m_Camera->GetRotation().x)});
	const glm::vec3 rightDir = cross(forwardDir, CameraUtility::UP_VECTOR);
	const auto dt = static_cast<float>(frameTime.DeltaTime()); 
	float calcMovementSpeed = m_MovementSpeed * dt;

	if (keyBuffer[KEY_LEFT_SHIFT])
		calcMovementSpeed *= 3.0f;
	if (keyBuffer[KEY_W])
		m_Velocity += forwardDir * calcMovementSpeed;
	if (keyBuffer[KEY_S])
		m_Velocity -= forwardDir * calcMovementSpeed;
	if (keyBuffer[KEY_D]) 
		m_Velocity += rightDir * calcMovementSpeed;
	if (keyBuffer[KEY_A]) 
		m_Velocity -= rightDir * calcMovementSpeed;
	if (keyBuffer[KEY_SPACE]) 
		m_Velocity += CameraUtility::UP_VECTOR * calcMovementSpeed;
	if (keyBuffer[KEY_LEFT_CTRL])
		m_Velocity -= CameraUtility::UP_VECTOR * calcMovementSpeed;

	m_Camera->SetPosition(m_Camera->GetPosition() + m_Velocity);
	m_Camera->UpdateViewModel(); 
}

void Player::OnMouseMove(const WindowHnd& window, const Vec2d& position) const {
	m_Camera->OnMouseMove(window, position); 
}

void Player::OnMouseScroll(const WindowHnd& window, const ScrollDirection& scrollDir) const {
	m_Camera->OnMouseScroll(window, scrollDir);
}

Camera& Player::GetCamera() const {
	return *m_Camera; 
}