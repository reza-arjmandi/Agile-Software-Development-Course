#pragma once
#include "ITaskRunner.h"

class MockTaskRunner : public ITaskRunner
{

public:
	MOCK_METHOD2(Create,
		std::unique_ptr<ITaskHandler>(
			std::launch launchPolicy, std::shared_ptr<ITask> task));

};