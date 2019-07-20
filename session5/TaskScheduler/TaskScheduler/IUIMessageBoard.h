#pragma once
#include <string>

class IUIMessageBoard
{

public:
	~IUIMessageBoard() = default;
	virtual void PushMessageToBoard(const std::string& message) = 0;

};