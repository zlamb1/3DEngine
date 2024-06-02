#pragma once

class ITexture {

public:
	virtual ~ITexture() = default;

	virtual void Bind() const = 0; 

};