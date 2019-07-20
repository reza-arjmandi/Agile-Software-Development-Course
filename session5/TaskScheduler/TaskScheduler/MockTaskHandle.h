#pragma once

#include "ITaskHandle.h"
#include "gmock/gmock.h"

class MockTaskHandle : public ITaskHandle
{

public :

	MOCK_METHOD1(WaitFor, std::future_status(const std::chrono::microseconds& duration));
	MOCK_METHOD0(Get, bool());

};