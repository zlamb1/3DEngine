#pragma once


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Event/Input/MouseScrollEvent.h"
#include "..\Math\Vec2d.h"
#include "Window/WindowHnd.h"

namespace CameraUtility {
	static glm::vec3 UP_VECTOR{ 0.0f, 1.0f, 0.0f };

	static glm::vec3 VectorInUnitSphere(glm::vec3 origin, float yaw, float pitch) {
		return origin + glm::vec3{
			sin(yaw) * cos(pitch), sin(pitch), cos(yaw) * cos(pitch)
		};
	}

	static glm::mat4 CreateProjectionMatrix(float fovy, float aspect, float zNear, float zFar) {
		return glm::perspective(fovy, aspect, zNear, zFar);
	}
}


class Camera {

public:
	virtual ~Camera() = default;

	virtual void OnMouseMove(const WindowHnd& window, const Vec2d& position) {} 
	virtual void OnMouseScroll(const WindowHnd& window, const ScrollDirection& scrollDir) {}

	virtual void UpdateViewModel() = 0;

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(const glm::vec3& newPosition) { m_Position = newPosition; }

	const glm::vec3 GetRotation() const { return m_Rotation; }
	void SetRotation(const glm::vec3& newRotation) { m_Rotation = newRotation; }

	const float& GetSensitivity() const { return m_MouseSens; }
	void SetSensitivity(float newSens) { m_MouseSens = newSens; }

protected:
	float m_MouseSens = 0.01f;
	glm::mat4 m_ProjectionMatrix{}, m_ViewMatrix{}, m_ViewProjectionMatrix{};
	glm::vec3 m_Position{}, m_Rotation{};

protected:
	void ClampPitch() {
		if (m_Rotation.y >= glm::radians(90.0f)) m_Rotation.y = glm::radians(89.99f);
		if (m_Rotation.y <= glm::radians(-90.0f)) m_Rotation.y = glm::radians(-89.99f);
	}

};