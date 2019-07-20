#pragma once
#include "IUIMessageBoard.h"
#include "gmock/gmock.h"

class MockUIMessageBoard : public IUIMessageBoard
{

public:
	MOCK_METHOD1(PushMessageToBoard, void(const std::string& message));

};