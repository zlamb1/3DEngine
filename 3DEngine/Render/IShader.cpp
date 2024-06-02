#include "Render/IShader.h"

#include "RendererAPI.h"

Ref<IShader> IShader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
	return RendererAPI::Instance().GetRenderCore().CreateShader(
		vertexSource, fragmentSource); 
}
