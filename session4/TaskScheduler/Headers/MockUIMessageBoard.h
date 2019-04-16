#pragma once
#include "IUIMessageBoard.h"

class MockUIMessageBoard : public IUIMessageBoard
{

public:
	MOCK_METHOD1(PushMessageToMessageBoard, void(const std::string& message));

};