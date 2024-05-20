#pragma once

#include <glm.hpp>

#include "Render/IShader.h"

class GLShader: public IShader {

public:
	GLShader(std::string_view vertSource, std::string_view fragSource);
	virtual ~GLShader() override;

	void BindShader() const override;

	int QueryUniformLocation(std::string_view name) const override;
	void SetMatrix4fv(std::string_view name, const glm::mat4& matrix) const override;

	bool m_ShaderError = false; 

private:
	unsigned int m_ProgramId = 0; 

};
