#pragma once
#include "ITask.h"
#include "ITaskHandler.h"

namespace BusinessRules
{

	class ITaskRunner
	{

	public:
		virtual ~ITaskRunner() = default;
		virtual std::unique_ptr<ITaskHandler> Create(
			std::launch launchPolicy, std::shared_ptr<Entities::ITask> task) = 0;

	};

}