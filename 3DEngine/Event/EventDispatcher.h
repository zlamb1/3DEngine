#pragma once

#include <functional>
#include <memory>

#include "EventHandler.h"

class EventDispatcher {

public:
	template<typename T>
	void Subscribe(std::shared_ptr<IEventHandler> eventHandler) {
		m_Callbacks[typeid(T).name()].emplace_back(eventHandler);
	}

	template <typename T>
	void Unsubscribe(std::shared_ptr<IEventHandler> eventHandler) {
		auto vec = m_Callbacks[typeid(T).name()];
		for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
			if (*iter == eventHandler) {
				vec.erase(iter);
				break;
			}
		}
	}

	template <typename T>
	void Dispatch(const IEvent& _event) const {
		const char* name = typeid(T).name();
		// no handlers subscribed to the event
		if (m_Callbacks.find(name) == m_Callbacks.end()) return;
		// found handlers
		for (const auto& eventHandler : 
			m_Callbacks.at(name)) {
			eventHandler->Dispatch(_event);
		}
	}

private:
	std::unordered_map<const char*, std::vector<std::shared_ptr<IEventHandler>>> m_Callbacks; 

};
