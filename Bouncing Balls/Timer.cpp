#include <iostream>

#include "Timer.h"

Timer::Timer()
{
	m_startTimePoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	stop();
}

void Timer::stop()
{
	auto endTimePoint = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

	long long duration = end - start;
	double ms = duration * 0.001;

	std::cout << "Timed at: " << duration << "us (" << ms << "ms)\n";
}