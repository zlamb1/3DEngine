#pragma once

#include "Render/IAttribLayout.h"

class GLAttribLayout: public IAttribLayout {

public:
	GLAttribLayout();
	~GLAttribLayout() override;

	void BindLayout() const override;

	void EnableAttrib(unsigned int attribindex) const override;
	void DisableAttrib(unsigned attribindex) const override;

	void AttribFormat(unsigned int attribindex, int size,
		ShaderAttrib::AttribType type, bool normalized, unsigned relativeoffset) const override;
	void AttribBinding(unsigned int attribindex, unsigned int bindingindex) const override;

private:
	unsigned int m_VAO; 

};
