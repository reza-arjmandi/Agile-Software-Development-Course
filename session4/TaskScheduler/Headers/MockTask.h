#pragma once
#include "ITask.h"

namespace Test
{

	class MockTask : public Entities::ITask
	{

	public:
		MOCK_METHOD0(Run, bool(void));

	};

}