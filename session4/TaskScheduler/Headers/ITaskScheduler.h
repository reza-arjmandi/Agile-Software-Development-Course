#pragma once

namespace BusinessRules
{

	class ITaskScheduler
	{

	public:
		virtual ~ITaskScheduler() = default;
		virtual void Run() = 0;
		virtual void Pull(std::chrono::milliseconds timeOut) = 0;
		virtual void Stop() = 0;

	};

}