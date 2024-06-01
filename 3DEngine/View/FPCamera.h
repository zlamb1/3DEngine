#pragma once

#include <vector>

#include "View/Camera.h"

class FPCamera: public Camera {

public:
	glm::mat4 CreateViewMatrix() const override;
	void ProcessMouseMove(const WindowHnd& window, double xpos, double ypos) override;

};