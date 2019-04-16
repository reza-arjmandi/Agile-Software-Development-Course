#pragma once

class ITask
{

public:
	virtual ~ITask() = default;
	virtual bool Run() = 0;

};