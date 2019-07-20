#pragma once
#include <chrono>
#include <future>

class ITaskHandle
{

public:
	~ITaskHandle() = default;

	virtual std::future_status WaitFor(const std::chrono::microseconds& duration) = 0;
	virtual bool Get() = 0;

};