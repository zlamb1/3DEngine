#pragma once

#include <memory>

#include "IAttribLayout.h"

#include "IO/ImageLoader.h"
#include "IShader.h"
#include "ITexture.h"
#include "View/Camera.h"

using std::unique_ptr; 

struct RenderProfile {
	const Camera& m_Camera;
	const glm::mat4& m_Projection; 
};

class RenderCore {

public:
	RenderCore() = default;
	virtual ~RenderCore() = default; 

	virtual bool InitializeCore() = 0;
	virtual void ShutdownCore() = 0;

	virtual void OnFrame() = 0; 

	virtual void SetViewport(int x, int y, int width, int height) = 0;
	virtual void SetDepthTest(bool enable); 

	virtual unique_ptr<IAttribLayout> CreateAttribLayout();
	virtual unique_ptr<IShader> CreateShader(std::string_view vertSource, 
		std::string_view fragSource) const = 0;
	virtual unique_ptr<ITexture> CreateTexture(const ImageLoader::ImageProfile& profile) const = 0;

	void SetClearColor(glm::vec4 newClearColor) {
		m_ClearColor = newClearColor; 
	}

protected:
	glm::vec4 m_ClearColor{}; 

};