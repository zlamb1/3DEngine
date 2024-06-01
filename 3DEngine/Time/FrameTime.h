#pragma once

class FrameTime {

public:
	void OnFrame(); 

	double DeltaTime() const; 

private:
	double m_LastFrameTime = 0; 

};