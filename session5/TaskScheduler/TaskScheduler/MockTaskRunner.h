#pragma once
#include "ITaskRunner.h"
#include "gmock/gmock.h"

class MockTaskRunner : public ITaskRunner
{

public:

	 MOCK_METHOD1(RunAsync, std::shared_ptr<ITaskHandle>(std::shared_ptr<ITask> task));
};