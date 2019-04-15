#pragma once

namespace Entities
{

	class ITask
	{

	public:
		virtual ~ITask() = default;
		virtual bool Run() = 0;

	};

}