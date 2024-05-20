#pragma once

#include "View/Camera.h"

class TPCamera: public Camera {

public:
	glm::mat4 CreateViewMatrix() const override;

	void ProcessMouseMove(const WindowHnd& window, double xpos, double ypos) override;
	void ProcessMouseScroll(const WindowHnd& window, double xoffset, double yoffset) override;

private:
	float m_Zoom = 3.0f; 

};
