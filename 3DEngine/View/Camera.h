#pragma once

#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

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

	virtual glm::mat4 CreateViewMatrix() const = 0;
	virtual void ProcessMouseMove(const WindowHnd& window, double xpos, double ypos) {};
	virtual void ProcessMouseScroll(const WindowHnd& window, double xoffset, double yoffset) {}
	virtual void ProcessKeyInput(const WindowHnd& window, const std::vector<bool>& keyBuffer) {};

protected:
	glm::vec3 m_Position{}, m_Rotation{};

	void ClampPitch() {
		if (m_Rotation.y >= glm::radians(90.0f)) m_Rotation.y = glm::radians(89.99f);
		if (m_Rotation.y <= glm::radians(-90.0f)) m_Rotation.y = glm::radians(-89.99f);
	}

};