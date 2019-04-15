#pragma once
#include "ITaskRunner.h"

namespace Test
{

	class MockTaskRunner : public BusinessRules::ITaskRunner
	{

	public:
		MOCK_METHOD2(Create, 
			std::unique_ptr<BusinessRules::ITaskHandler>(
				std::launch launchPolicy, std::shared_ptr<Entities::ITask> task));

	};

}