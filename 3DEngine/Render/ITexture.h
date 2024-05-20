#pragma once

class ITexture {

public:
	virtual ~ITexture() = default; 
	virtual void BindTexture() const = 0; 

};