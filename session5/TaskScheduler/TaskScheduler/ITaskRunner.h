#pragma once
#include "ITask.h"
#include "ITaskHandle.h"

#include <memory>

class ITaskRunner
{

public:
	~ITaskRunner() = default;

	virtual std::shared_ptr<ITaskHandle> RunAsync(std::shared_ptr<ITask> task) = 0;

};