#pragma once
#include "IUIMessageBoard.h"

namespace Test
{

	class MockUIMessageBoard : public BusinessRules::IUIMessageBoard
	{

	public:
		MOCK_METHOD1(PushMessageToMessageBoard, void(const std::string& message));

	};

}