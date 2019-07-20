#pragma once
#include <chrono>

class ITaskScheduler
{

public:
	~ITaskScheduler() = default;

	virtual void Run() = 0;
	virtual void Pull(const std::chrono::milliseconds& duration) = 0;

};
