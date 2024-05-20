#include "BlockGameEngine.h"

#include <iostream>
#include <fstream>

#include "IO/FileReader.h"
#include "IO/STB/STBImageLoader.h"
#include "Render/GL/GLRenderCore.h"
#include "View/TPCamera.h"
#include "Window/GLFW/GLFWWindowCore.h"
#include "Window/GLFW/GLFWWindowHnd.h"

BlockGameEngine::BlockGameEngine() : GameEngine(GLFWWindowCore::Instance(), GLRenderCore::Instance()) {
	m_WindowHnd = std::make_unique<GLFWWindowHnd>("BlockGame");
	m_Camera = std::make_shared<TPCamera>();
	m_ImageLoader = std::make_shared<STBImageLoader>(true); 
}

bool BlockGameEngine::SetupEngine() {
	m_RenderCore.SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

	auto vertShader = ReadFile("Shader/chunk.vert");
	auto fragShader = ReadFile("Shader/chunk.frag");
	if (vertShader.HasValue()) {
		m_ChunkShader = m_RenderCore.CreateShader(vertShader.GetValue(), fragShader.GetValue());
	} else {
		LOG_WARN("Failed to Read Chunk Shader")
		return false; 
	}

	m_ShaderLayout = m_RenderCore.CreateAttribLayout();
	m_ShaderLayout->BindLayout();
	m_ShaderLayout->EnableAttrib(0);
	m_ShaderLayout->AttribFormat(0, 3, ShaderAttrib::FLOAT, false, 0);
	m_ShaderLayout->AttribBinding(0, 0);

	constexpr float data[] = {
		-0.5f, 0.5f, 0, -0.5f, -0.5f, 0, 0.5f, -0.5f, 0
	};
	
	GLCall(glGenBuffers(1, &m_VBO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO)); 
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW)); 

	return true; 
}

void BlockGameEngine::OnFrame() {
	m_ShaderLayout->BindLayout();
	GLCall(glBindVertexBuffer(0, m_VBO, 0, sizeof(float) * 3));
	m_ChunkShader->BindShader();
	m_ChunkShader->SetMatrix4fv("m_Projection", m_Projection);
	m_ChunkShader->SetMatrix4fv("m_View", m_Camera->CreateViewMatrix());
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 3)); 
}