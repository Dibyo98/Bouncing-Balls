#include "FrameTime.h"

FrameTime::FrameTime(float& frameTime)
	: m_frameTime(frameTime)
{
	m_startTimePoint = std::chrono::high_resolution_clock::now();
}

FrameTime::~FrameTime()
{
	stop();
}

void FrameTime::stop()
{
	auto endTimePoint = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	m_frameTime = (end - start) * 0.001f;
}