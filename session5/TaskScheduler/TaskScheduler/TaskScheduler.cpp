#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(const std::vector<State>& stateMachineMap,
	std::shared_ptr<IUIMessageBoard> messageBoard,
	std::shared_ptr<ITaskRunner> taskRunner) :
	m_StateMachineMap(stateMachineMap),
	m_MessageBoard(messageBoard),
	m_TaskRunner(taskRunner)
{
}

void TaskScheduler::Run()
{
	if (m_CurrentTaskIndex != InitialState)
	{
		return;
	}
	m_CurrentTaskIndex = 0;
	m_TaskHandle = m_TaskRunner->RunAsync(m_StateMachineMap[m_CurrentTaskIndex].Task);
}

void TaskScheduler::Pull(const std::chrono::milliseconds& duration)
{
	if (m_CurrentTaskIndex == InitialState)
	{
		return;
	}
	if (m_TaskHandle->WaitFor(duration) == std::future_status::ready)
	{
		auto taskResult = m_TaskHandle->Get();
		UpdateMessageBoard(taskResult);
		UpdateCurrentIndex(taskResult);
		if (m_CurrentTaskIndex != InitialState)
		{
			m_TaskHandle = m_TaskRunner->RunAsync(m_StateMachineMap[m_CurrentTaskIndex].Task);
		}
	}
}

void TaskScheduler::UpdateMessageBoard(bool taskResult)
{
	if (taskResult)
	{
		m_MessageBoard->PushMessageToBoard(m_StateMachineMap[m_CurrentTaskIndex].DescriptionOnSuccessfull);
	}
	else
	{
		m_MessageBoard->PushMessageToBoard(m_StateMachineMap[m_CurrentTaskIndex].DescriptionOnFailure);
	}
}

void TaskScheduler::UpdateCurrentIndex(bool taskResult)
{
	m_CurrentTaskIndex = taskResult ?
		m_StateMachineMap[m_CurrentTaskIndex].NextTaskIndexOnSuccessful :
		m_StateMachineMap[m_CurrentTaskIndex].NextTaskIndexOnFailure;
}
