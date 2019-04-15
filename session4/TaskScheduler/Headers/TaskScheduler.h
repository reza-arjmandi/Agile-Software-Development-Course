#pragma once
#include "ITaskScheduler.h"

#include "ITask.h"
#include "ITaskRunner.h"
#include "IUIMessageBoard.h"
#include "ITaskHandler.h"

namespace BusinessRules
{

	class TaskScheduler : public ITaskScheduler
	{

	public:
		static constexpr int InitialState = -1;

		struct StateMachine
		{
			std::shared_ptr<Entities::ITask> Task;
			int NextTaskIndexOnSuccessful;
			int NextTaskIndexOnFail;
			std::string SuccessfullMessage;
			std::string FailedMessage;
		};

		TaskScheduler(
			std::unique_ptr<ITaskRunner> taskRunner, 
			std::vector<StateMachine> stateMachineMap, 
			IUIMessageBoard& uiMessageBoard);

		void Run() override;
		void Pull(std::chrono::milliseconds timeOut) override;
		void Stop() override;

	private:
		std::vector<StateMachine> m_StateMachineMap;
		IUIMessageBoard& m_UiMessageBoard;
		std::unique_ptr<ITaskRunner> m_TaskRunner;
		int m_CurrentStateIndex = -1;
		std::unique_ptr<ITaskHandler> m_CurrentTaskHandler;
	};

}