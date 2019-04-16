#pragma once
#include "ITask.h"

class MockTask : public ITask
{

public:
	MOCK_METHOD0(Run, bool(void));

};