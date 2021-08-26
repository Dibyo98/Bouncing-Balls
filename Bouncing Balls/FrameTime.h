#pragma once
#include <chrono>

class FrameTime
{
public:
	FrameTime(float& frameTime);
	~FrameTime();
	void stop();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
	float& m_frameTime;
};