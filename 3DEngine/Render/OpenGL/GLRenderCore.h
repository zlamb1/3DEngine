#pragma once

#include <string>

#include <glad/glad.h>

#include "Logger.h"

#include "Render/ITexture.h"
#include "Render/RenderCore.h"

#ifdef NDEBUG
#define GLCall(f) f;
#else
#define GLCall(f) while(glGetError() != GL_NO_ERROR);\
	f;\
	if (!GLLogError()) __debugbreak();
#endif

static bool GLLogError() {
	while (const GLenum error = glGetError()) {
		LOG_ERROR("[RenderCore] : OpenGL error: " + std::to_string(error))
		return false;
	}
	return true;
}

class GLRenderCore: public RenderCore {

public:
	static GLRenderCore& Instance() {
		static GLRenderCore renderCore{};
		return renderCore;
	}

	bool InitializeCore() override;
	void ShutdownCore() override;

	void OnFrame() override; 

	void SetViewport(int x, int y, int width, int height) override;
	void SetCullFace(FaceType faceType) override;
	void SetFrontFace(WindingOrder windingOrder) override;

	void EnableDepthTesting(bool enabled) override;
	void EnableFaceCulling(bool enabled) override;
	void EnableWireframeMode(bool enabled) override;

	Ref<IAttribLayout> CreateAttribLayout() const override;
	Ref<Mesh> CreateMesh() const override;
	Ref<IShader> CreateShader(std::string_view vertSource,
		std::string_view fragSource) const override;
	Ref<ITexture> CreateTexture2D(const ImageInfo& imageInfo) const override;

private:
	GLRenderCore() = default;

};