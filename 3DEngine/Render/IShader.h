#pragma once

#include <string_view>

#include <glm.hpp>

#include "Ref.h"

class IShader {

public:
	virtual ~IShader() = default; 

	virtual void Bind() const = 0;

	virtual int QueryUniformLocation(std::string_view name) const = 0;
	virtual void SetMatrix4fv(std::string_view name, const glm::mat4& matrix) const = 0;

	static Ref<IShader> Create(const std::string& vertexSource, const std::string& fragmentSource);

};
