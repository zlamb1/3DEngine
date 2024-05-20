#pragma once

namespace ShaderAttrib {
	enum AttribType {
		FLOAT
	};
}

class IAttribLayout {

public:
	virtual ~IAttribLayout() = default; 

	virtual void BindLayout() const = 0;

	virtual void EnableAttrib(unsigned int attribindex) const = 0;
	virtual void DisableAttrib(unsigned int attribindex) const = 0;

	virtual void AttribFormat(unsigned int attribindex, int size,
		ShaderAttrib::AttribType type, bool normalized, unsigned int relativeoffset) const = 0;
	virtual void AttribBinding(unsigned int attribindex, unsigned int bindingindex) const = 0;

};