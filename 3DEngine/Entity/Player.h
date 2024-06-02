#pragma once

#include <memory>

#include "Ref.h"

#include "Event/Input/KeyPressEvent.h"
#include "Event/Input/MouseScrollEvent.h"

#include "Time/FrameTime.h"

#include "View/Camera.h"

class Player {

public:
	Player(Scope<Camera> camera); 

	void OnFrame(const std::vector<KeyAction>& keyBuffer, const FrameTime& frameTime);
	void OnMouseMove(const WindowHnd& window, const Vec2d& position) const;
	void OnMouseScroll(const WindowHnd& window, const ScrollDirection& scrollDir) const;

	Camera& GetCamera() const; 

private:
	float m_MovementSpeed = 1.0f, m_ExpFriction = 0.995f; 

	Scope<Camera> m_Camera;
	glm::vec3 m_Velocity{};

};
