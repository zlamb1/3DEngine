#pragma once

#include <functional>

#include "IEvent.h"

class IEventHandler {

public:
	virtual ~IEventHandler() = default;

	virtual void Dispatch(const IEvent& _event) = 0;
};

template<typename T>
class EventHandler : public IEventHandler {

public:
	EventHandler(std::function<void(const T&)> callback) : m_Callback(callback) {
		
	}

	void Dispatch(const IEvent& _event) override {
		const T& t = dynamic_cast<const T&>(_event); 
		m_Callback(t);
	}

private:
	std::function<void(T)> m_Callback; 

};