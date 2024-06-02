#pragma once

#include <vector>

#include "View/Camera.h"

class FPCamera: public Camera {

public:
	void OnMouseMove(const WindowHnd& window, const Vec2d& position) override;

	void UpdateViewModel() override;

};