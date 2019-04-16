#include "pch.h"
#include "TaskScheduler.h"

TaskScheduler::TaskScheduler(
	std::unique_ptr<ITaskRunner> taskRunner, 
	std::vector<StateMachine> stateMachineMap, 
	IUIMessageBoard & const uiMessageBoard) :
	m_TaskRunner(std::move(taskRunner)),
	m_StateMachineMap(stateMachineMap),
	m_UiMessageBoard(uiMessageBoard)
{
}

void TaskScheduler::Run()
{
	if (m_CurrentStateIndex != InitialState)
	{
		return;
	}

	m_CurrentStateIndex = 0;
	m_CurrentTaskHandler = m_TaskRunner->Create(std::launch::async, m_StateMachineMap[m_CurrentStateIndex].Task);
}

void TaskScheduler::Pull(std::chrono::milliseconds timeOut)
{
	if (m_CurrentStateIndex == InitialState)
	{
		return;
	}

	if (m_CurrentTaskHandler->WaitFor(timeOut) == std::future_status::ready)
	{
		if (m_CurrentTaskHandler->Get())
		{
			m_UiMessageBoard.PushMessageToMessageBoard(m_StateMachineMap[m_CurrentStateIndex].SuccessfullMessage);

			m_CurrentStateIndex = m_StateMachineMap[m_CurrentStateIndex].NextTaskIndexOnSuccessful;
			if (m_CurrentStateIndex != InitialState)
			{
				m_CurrentTaskHandler = m_TaskRunner->Create(
					std::launch::async, m_StateMachineMap[m_CurrentStateIndex].Task);
			}
		}
		else
		{
			m_UiMessageBoard.PushMessageToMessageBoard(m_StateMachineMap[m_CurrentStateIndex].FailedMessage);
			m_CurrentStateIndex = m_StateMachineMap[m_CurrentStateIndex].NextTaskIndexOnFail;
		}
	}
}

void TaskScheduler::Stop()
{
	m_CurrentStateIndex = InitialState;
}