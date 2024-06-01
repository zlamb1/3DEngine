#pragma once

#include <memory>

#include "View/Camera.h"

class Player {

public:
	Player(std::unique_ptr<Camera> camera); 

	void OnFrame(const std::vector<bool>& keyBuffer, const FrameTime& frameTime);
	void OnMouseMove(const WindowHnd& window, double xpos, double ypos) const;
	void OnMouseScroll(const WindowHnd& window, double xoffset, double yoffset) const; 

	float& MouseSensitivity() const;

	glm::mat4 CreateViewMatrix() const;

private:
	float m_MovementSpeed = 1.0f, m_ExpFriction = 0.995f; 

	std::unique_ptr<Camera> m_Camera;
	glm::vec3 m_Velocity{};

};
