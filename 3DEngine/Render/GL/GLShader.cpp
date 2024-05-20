#include "GLShader.h"

#include <glad/glad.h>

#include "GLRenderCore.h"
#include "Logger.h"

GLShader::GLShader(std::string_view vertSource, std::string_view fragSource) {
	const unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER), fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	int success;
	char infoLog[512];

	const char* aVertSource = vertSource.data();
	const char* aFragSource = fragSource.data(); 

	GLCall(glShaderSource(vertShader, 1, &aVertSource, nullptr));
	GLCall(glCompileShader(vertShader));
	GLCall(glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success));
	if (!success) {
		m_ShaderError = true;
		GLCall(glGetShaderInfoLog(vertShader, 512, nullptr, infoLog));
		LOG_WARN("[GL] Failed to Compile Vertex Shader : " << infoLog);
		return; 
	}

	GLCall(glShaderSource(fragShader, 1, &aFragSource, nullptr));
	GLCall(glCompileShader(fragShader));
	GLCall(glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success));
	if (!success) {
		m_ShaderError = true;
		GLCall(glGetShaderInfoLog(fragShader, 512, nullptr, infoLog));
		LOG_WARN("[GL] Failed to Compile Fragment Shader : " << infoLog);
		return;
	}

	m_ProgramId = glCreateProgram();
	GLCall(glAttachShader(m_ProgramId, vertShader));
	GLCall(glAttachShader(m_ProgramId, fragShader));
	GLCall(glLinkProgram(m_ProgramId));
	GLCall(glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success));
	if (!success) {
		m_ShaderError = true;
		GLCall(glGetProgramInfoLog(m_ProgramId, 512, nullptr, infoLog));
		LOG_WARN("[GL] Failed to Link Program : " << infoLog);
		return; 
	}

	GLCall(glDeleteShader(vertShader));
	GLCall(glDeleteShader(fragShader));
}

GLShader::~GLShader() {
	GLCall(glDeleteProgram(m_ProgramId));
}

void GLShader::BindShader() const {
	GLCall(glUseProgram(m_ProgramId));
}

int GLShader::QueryUniformLocation(std::string_view name) const {
	return glGetUniformLocation(m_ProgramId, name.data());
}

void GLShader::SetMatrix4fv(std::string_view name, const glm::mat4& mat) const {
	const int uniformLocation = QueryUniformLocation(name);
	if (uniformLocation > -1) {
		GLCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0])); 
	} else {
		LOG_WARN("[GL] Failed to Set Shader Uniform (Matrix4fv)")
	}
}