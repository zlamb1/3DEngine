#include "BlockGameEngine.h"

#include <iostream>
#include <fstream>

#include "Event/Input/MouseMoveEvent.h"

#include "IO/FileReader.h"
#include "IO/STB/STBImageLoader.h"

#include "Render/Vertex.h"
#include "Render/GL/GLRenderCore.h"

#include "View/FPCamera.h"
#include "Window/GLFW/GLFWWindowCore.h"
#include "Window/GLFW/GLFWWindowHnd.h"

BlockGameEngine::BlockGameEngine() : GameEngine(GLFWWindowCore::Instance(), GLRenderCore::Instance()) {
	auto camera = std::make_unique<FPCamera>(); 
	m_Player = std::make_unique<Player>(std::move(camera)); 
	m_WindowHnd = std::make_unique<GLFWWindowHnd>("BlockGame");
	m_ImageLoader = std::make_shared<STBImageLoader>(true); 
}

bool BlockGameEngine::SetupEngine() {
	m_RenderCore.SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

	auto vertShader = ReadFile("Shader/chunk.vert");
	auto fragShader = ReadFile("Shader/chunk.frag");
	if (vertShader.HasValue()) {
		m_ChunkShader = m_RenderCore.CreateShader(
			vertShader.GetValue(), fragShader.GetValue());
	} else {
		LOG_WARN("Failed to Read Chunk Shader")
		return false; 
	}

	m_ShaderLayout = m_RenderCore.CreateAttribLayout();
	m_ShaderLayout->BindLayout();

	m_ShaderLayout->EnableAttrib(0);
	m_ShaderLayout->AttribFormat(0, 3, ShaderAttrib::FLOAT, 
		false, offsetof(Vertex, Vertex::x));
	m_ShaderLayout->AttribBinding(0, 0);

	auto mesh = m_RenderCore.CreateMesh(); 
	m_Chunk = std::make_unique<Chunk>(std::move(mesh));

	m_Player->MouseSensitivity() = 0.004f; 

	m_WindowHnd->SetCursorHidden(true);

	const auto mouseMoveHandler = std::make_shared<EventHandler<MouseMoveEvent>>(
		[&](const MouseMoveEvent& _event) {
			m_WindowHnd->SetCursorCentered();
	});

	m_WindowHnd->GetEventDispatcher().Subscribe<MouseMoveEvent>(mouseMoveHandler);

	m_RenderCore.EnableFaceCulling(true);

	return true; 
}

void BlockGameEngine::OnFrame() {
	m_ShaderLayout->BindLayout();
	m_ChunkShader->BindShader();
	m_ChunkShader->SetMatrix4fv("m_Projection", m_Projection);
	m_ChunkShader->SetMatrix4fv("m_View", m_Player->CreateViewMatrix());
	m_Chunk->DrawChunk();

	if (m_KeyBuffer[GLFW_KEY_C]) {
		m_Wireframe.SetState(!m_Wireframe.GetState());
		m_RenderCore.EnableWireframeMode(m_Wireframe.GetState());
	}
}