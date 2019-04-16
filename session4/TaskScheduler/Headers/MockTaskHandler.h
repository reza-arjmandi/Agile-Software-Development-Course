#pragma once
#include "ITaskHandler.h"

class MockTaskHandler : public ITaskHandler
{

public:
	MOCK_METHOD1(WaitFor, std::future_status(const std::chrono::milliseconds& miliSeconds));
	MOCK_METHOD0(Get, bool(void));

};