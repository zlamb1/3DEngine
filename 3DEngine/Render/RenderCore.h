#pragma once

#include <memory>

#include "ITexture2D.h"
#include "Ref.h"

#include "IO/ImageLoader.h"

#include "Render/IAttribLayout.h"
#include "Render/IShader.h"
#include "Render/Mesh.h"

enum class FaceType : int {
	FRONT, BACK, FRONT_AND_BACK
};

enum class WindingOrder : int {
	CW, CCW
};

class RenderCore {

public:
	RenderCore() = default;
	virtual ~RenderCore() = default; 

	virtual bool InitializeCore() = 0;
	virtual void ShutdownCore() = 0;

	virtual void OnFrame() = 0; 

	virtual void SetViewport(int x, int y, int width, int height) = 0;
	virtual void SetCullFace(FaceType faceType) = 0; 
	virtual void SetFrontFace(WindingOrder windingOrder) = 0; 

	virtual void EnableDepthTesting(bool enabled) = 0;
	virtual void EnableFaceCulling(bool enabled) = 0;
	virtual void EnableWireframeMode(bool enabled) = 0; 

	virtual Ref<IAttribLayout> CreateAttribLayout() const = 0;
	virtual Ref<Mesh> CreateMesh() const = 0;
	virtual Ref<IShader> CreateShader(std::string_view vertSource,
		std::string_view fragSource) const = 0;
	virtual Ref<ITexture> CreateTexture2D(const ImageInfo& imageInfo) const = 0;

	void SetClearColor(glm::vec4 newClearColor) {
		m_ClearColor = newClearColor; 
	}

protected:
	glm::vec4 m_ClearColor{}; 

};