#pragma once

namespace BusinessRules
{

	class ITaskHandler
	{

	public:
		virtual ~ITaskHandler() = default;
		virtual std::future_status WaitFor(const std::chrono::milliseconds& miliSeconds) = 0;
		virtual bool Get() = 0;

	};

}