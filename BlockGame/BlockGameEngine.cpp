#include "BlockGameEngine.h"

#include <iostream>
#include <fstream>

#include "Event/Input/MouseMoveEvent.h"

#include "IO/FileReader.h"
#include "IO/STB/STBImageLoader.h"

#include "Render/Vertex.h"
#include "Render/OpenGL/GLRenderCore.h"

#include "View/Perspective/FPCamera.h"
#include "Window/GLFW/GLFWWindowCore.h"
#include "Window/GLFW/GLFWWindowHnd.h"

BlockGameEngine::BlockGameEngine() : GameEngine(GLFWWindowCore::Instance()) {
	auto camera = CreateScope<FPCamera>(); 
	m_Player = CreateScope<Player>(std::move(camera)); 
	m_Window = CreateRef<GLFWWindowHnd>("BlockGame");
	m_ImageLoader = CreateRef<STBImageLoader>(true); 
}

bool BlockGameEngine::SetupEngine() {
	GetRenderCore().SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });

	auto vertexShader = ReadFile("Shader/chunk.vert");
	auto fragmentShader = ReadFile("Shader/chunk.frag");
	if (vertexShader.HasValue() && fragmentShader.HasValue()) {
		m_ChunkShader = IShader::Create(vertexShader.GetValue(), 
			fragmentShader.GetValue());
	} else {
		LOG_WARN("Failed to Read Chunk Shader")
		return false; 
	}

	m_ShaderLayout = GetRenderCore().CreateAttribLayout();
	m_ShaderLayout->BindLayout();

	m_ShaderLayout->EnableAttrib(0);
	m_ShaderLayout->AttribFormat(0, 3, AttribType::FLOAT,
		false, offsetof(Vertex, Vertex::x));
	m_ShaderLayout->AttribBinding(0, 0);

	auto mesh = GetRenderCore().CreateMesh(); 
	m_Chunk = CreateRef<Chunk>(mesh);

	m_Player->GetCamera().SetSensitivity(0.004f); 

	m_Window->SetCursorHidden(true);

	auto& eventDispatcher = m_Window->GetEventDispatcher();
	eventDispatcher.Subscribe<MouseMoveEvent>(
		CreateRef<EventHandler<MouseMoveEvent>>(
		[&](const MouseMoveEvent& _event) {
			if (m_Window->GetWindowAttrib(WindowAttrib::FOCUSED)) {
				m_Window->SetCursorCentered();
				m_Player->GetCamera().OnMouseMove(*m_Window,
					{ _event.xPos, _event.yPos });
			}
	}));

	GetRenderCore().EnableFaceCulling(true);

	return true; 
}

void BlockGameEngine::OnFrame() {
	// rendering
	m_ShaderLayout->BindLayout();
	m_ChunkShader->Bind();
	m_ChunkShader->SetMatrix4fv("m_Projection", m_Projection);
	m_ChunkShader->SetMatrix4fv("m_View", m_Player->GetCamera().GetViewMatrix());
	m_Chunk->DrawChunk();

	// input checking
	m_Player->OnFrame(m_KeyBuffer, m_FrameTime); 

	if (m_KeyBuffer[KEY_C] != RELEASE) {
		m_Wireframe.SetState(!m_Wireframe.GetState());
		GetRenderCore().EnableWireframeMode(m_Wireframe.GetState());
	}
}