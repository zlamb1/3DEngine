#pragma once

#include "RenderCore.h"

enum class RenderAPI : int {
	OpenGL
};

class RendererAPI {

public:
	static RendererAPI& Instance();
	RenderCore& GetRenderCore() const; 

	void InitializeAPI(RenderAPI api);

	RenderAPI GetRenderAPI() const;
	bool IsInitialized() const;

private:
	RendererAPI() = default;
	~RendererAPI() = default; 

private:
	bool m_Initialized = false; 
	RenderAPI m_API = RenderAPI::OpenGL;

};