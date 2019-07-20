#pragma once
#include "ITaskScheduler.h"
#include "IUIMessageBoard.h"
#include "ITask.h"
#include "ITaskRunner.h"

#include <vector>
#include <memory>

class TaskScheduler : public ITaskScheduler
{
public:

	struct State
	{
		std::shared_ptr<ITask> Task;
		std::string DescriptionOnSuccessfull;
		std::string DescriptionOnFailure;
		int NextTaskIndexOnSuccessful;
		int NextTaskIndexOnFailure;
	};

	const static int InitialState = -1;

	TaskScheduler(const std::vector<State>& stateMachineMap,
		std::shared_ptr<IUIMessageBoard> messageBoard,
		std::shared_ptr<ITaskRunner> taskRunner);
	virtual void Run() override;
	virtual void Pull(const std::chrono::milliseconds& duration) override;

private:

	void UpdateMessageBoard(bool taskResult);
	void UpdateCurrentIndex(bool taskResult);

	std::vector<State> m_StateMachineMap;
	std::shared_ptr<IUIMessageBoard> m_MessageBoard;
	std::shared_ptr<ITaskRunner> m_TaskRunner;
	std::shared_ptr<ITaskHandle> m_TaskHandle;
	int m_CurrentTaskIndex = InitialState;
};