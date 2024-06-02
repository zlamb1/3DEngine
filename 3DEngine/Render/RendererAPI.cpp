#include "RendererAPI.h"

#include "OpenGL/GLRenderCore.h"

RendererAPI& RendererAPI::Instance() {
	static RendererAPI api;
	if (!api.IsInitialized()) {
		// default to OpenGL render API
		api.InitializeAPI(RenderAPI::OpenGL); 
	}

	return api;
}

RenderCore& RendererAPI::GetRenderCore() const {
	switch (m_API) {
	case RenderAPI::OpenGL:
		return GLRenderCore::Instance();
	}

	// assert
	return GLRenderCore::Instance();
}


void RendererAPI::InitializeAPI(RenderAPI api) {
	if (m_Initialized) {
		auto& core = GetRenderCore();
		core.ShutdownCore();
	}
	m_API = api;
	auto& core = GetRenderCore();
	core.InitializeCore();
	m_Initialized = true;
}

RenderAPI RendererAPI::GetRenderAPI() const {
	return m_API; 
}


bool RendererAPI::IsInitialized() const {
	return m_Initialized; 
}