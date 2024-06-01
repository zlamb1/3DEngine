#pragma once

#include <chrono>
#include <ctime>  

namespace TimeUtil {
	static double EpochMilliseconds() {
		using namespace std::chrono;
		return duration<double>(system_clock::now().time_since_epoch()).count(); 
	}
}

template<typename T>
class StateTracker {

public:
	StateTracker() {}
	StateTracker(double delay) : m_Delay(delay) {}
	StateTracker(double delay, bool allowRepeat) : m_Delay(delay), m_AllowRepeat(allowRepeat) {}

	T GetState() const {
		return m_State; 
	}

	void SetState(T newState) {
		const auto time = TimeUtil::EpochMilliseconds();
		if (time > m_LastChange + m_Delay) {
			m_State = newState;
			m_LastChange = time;
		}
	}

	void SetAllowRepeat(bool allowRepeat) {
		m_AllowRepeat = allowRepeat;
	}

private:
	T m_State;
	double m_Delay = 0, m_LastChange;
	bool m_AllowRepeat = true;

};