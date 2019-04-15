#include "pch.h"
#include "TaskScheduler.h"
#include "MockUIMessageBoard.h"
#include "MockTaskRunner.h"
#include "MockTask.h"
#include "MockTaskHandler.h"

using namespace BusinessRules;
using namespace Test;

class TaskSchedulerTest : public testing::Test
{

protected:
	std::vector<TaskScheduler::StateMachine> StateMachineMap1;
	std::vector<TaskScheduler::StateMachine> StateMachineMap2;
	testing::StrictMock<MockUIMessageBoard> m_UIMessageBoard;
	testing::StrictMock<MockTaskRunner>* m_TaskRunnerPtrCaptured;
	std::unique_ptr<testing::StrictMock<MockTaskRunner>> m_TaskRunner;
	std::chrono::milliseconds m_TimeOut = std::chrono::milliseconds(100);

	void SetUp() override
	{
		m_TaskRunner = std::make_unique<testing::StrictMock<MockTaskRunner>>();
		m_TaskRunnerPtrCaptured = m_TaskRunner.get();

		//*************************************************
		// S: Successful
		// F: Fail
		//***************** StateMachineMap1 **************
		//
		//						 Initial
		//							|
		//						  Task0
		//						    |
		//						  S/ \F
		//					  Task1   Initial
		//						|
		//					  S/ \F
		//				  Task2   Initial
		//					|
		//				  S/ \F
		//			  Task3   Initial
		//				|
		//			  S/ \F
		//		initial   Initial
		//
		//*************************************************
		StateMachineMap1.push_back({ std::make_shared<testing::StrictMock<MockTask>>(),
			1, TaskScheduler::InitialState, "task0 successful", "task0 failed" });
		StateMachineMap1.push_back({ std::make_shared<testing::StrictMock<MockTask>>(), 
			2, TaskScheduler::InitialState, "task1 successful", "task1 failed" });
		StateMachineMap1.push_back({ std::make_shared<testing::StrictMock<MockTask>>(), 
			3, TaskScheduler::InitialState, "task2 successful", "task2 failed" });
		StateMachineMap1.push_back({ std::make_shared<testing::StrictMock<MockTask>>(), 
			TaskScheduler::InitialState, TaskScheduler::InitialState, "task3 successful", "task3 failed" });

		//*************************************************
		// S: Successful
		// F: Fail
		//***************** StateMachineMap2 **************
		//
		//  					 Initial
		//  						|
		//  					  Task0
		//  					    |
		//  					  S/ \F
		//  				  Task1   Task3
		//  					|		   \
		//  				  S/ \F			\
		//  			  Task2   Initial	 \
		//  				|				S/\F
		//  			  S/ \F				/  \
		//  		  Task1   \________Task4	Initial
		//  							 |
		//  						   S/ \F
		//  					 Initial   Initial
		//  
		//*************************************************
		StateMachineMap2.push_back({ std::make_shared<testing::StrictMock<MockTask>>(),
			1, 3, "task0 successful", "task0 failed" });
		StateMachineMap2.push_back({ std::make_shared<testing::StrictMock<MockTask>>(),
			2, TaskScheduler::InitialState, "task1 successful", "task1 failed" });
		StateMachineMap2.push_back({ std::make_shared<testing::StrictMock<MockTask>>(),
			1, 4, "task2 successful", "task2 failed" });
		StateMachineMap2.push_back({ std::make_shared<testing::StrictMock<MockTask>>(),
			4, TaskScheduler::InitialState, "task3 successful", "task3 failed" });
		StateMachineMap2.push_back({ std::make_shared<testing::StrictMock<MockTask>>(),
			TaskScheduler::InitialState, TaskScheduler::InitialState, "task4 successful", "task4 failed" });
	}

	auto GenerateTaskHandler()
	{
		auto taskHandler = std::make_unique<testing::StrictMock<MockTaskHandler>>();
		auto taskHandlerPtr = taskHandler.get();
		return std::make_tuple(std::move(taskHandler), taskHandlerPtr);
	}

};

// Expected Test Scenario:
// initial -> Task0 -> S -> Task1 -> S -> Task2 -> S -> Task3 -> S -> initial
TEST_F(TaskSchedulerTest, GivenStateMachineMap1WhenTaskSchedulerRunAndPullIsCalledRespectivelyThenExpectedTestScenraioMustBeRun_TestCase1)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	//When:
	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));   
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[0].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[1].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[1].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[2].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[2].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[3].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[3].SuccessfullMessage)).Times(1);

	taskScheduler->Pull(m_TimeOut);

	taskScheduler->Pull(m_TimeOut);
}

// Expected Test Scenario:
// initial -> Task0 -> S -> Task1 -> S -> Task2 -> S -> Task3 -> S -> initial
TEST_F(TaskSchedulerTest, GivenStateMachineMap1WhenTaskSchedulerRunAndPullIsCalledRespectivelyThenExpectedTestScenraioMustBeRun_TestCase2)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	//When:
	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::timeout));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[0].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[1].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[1].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[2].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::deferred));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[2].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[3].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[3].SuccessfullMessage)).Times(1);

	taskScheduler->Pull(m_TimeOut);

	taskScheduler->Pull(m_TimeOut);
}

// Expected Test Scenario:
// initial -> Task0 -> F -> initial
TEST_F(TaskSchedulerTest, GivenStateMachineMap1WhenTaskSchedulerRunAndPullIsCalledRespectivelyThenExpectedTestScenraioMustBeRun_TestCase3)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	//When:
	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(false));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[0].FailedMessage)).Times(1);

	taskScheduler->Pull(m_TimeOut);
	
	taskScheduler->Pull(m_TimeOut);
}

// Expected Test Scenario:
// initial -> Task0 -> S -> Task1 -> F -> initial
TEST_F(TaskSchedulerTest, GivenStateMachineMap1WhenTaskSchedulerRunAndPullIsCalledRespectivelyThenExpectedTestScenraioMustBeRun_TestCase4)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	//When:
	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[0].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[1].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(false));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[1].FailedMessage)).Times(1);

	taskScheduler->Pull(m_TimeOut);

	taskScheduler->Pull(m_TimeOut);
}

TEST_F(TaskSchedulerTest, GivenStateMachineMap1WhenTaskSchedulerRunIsCalledTwiceThenSecondCallMustBeNothingDone_TestCase1)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	//When:
	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	taskScheduler->Run();
}

TEST_F(TaskSchedulerTest, GivenStateMachineMap1WhenTaskSchedulerRunIsCalledTwiceThenSecondCallMustBeNothingDone_TestCase2)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	//When:
	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[0].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[1].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Run();
	taskScheduler->Run();
	taskScheduler->Run();

	taskScheduler->Pull(m_TimeOut);

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(false));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[1].FailedMessage)).Times(1);

	taskScheduler->Pull(m_TimeOut);

	taskScheduler->Pull(m_TimeOut);
}

TEST_F(TaskSchedulerTest, GivenARunningTaskSchedulerWhenTaskSchedulerStopIsCalledThenCallOfPullMustBeNothingDone)
{
	//Given:
	auto taskScheduler = std::make_unique<TaskScheduler>(std::move(m_TaskRunner), StateMachineMap1, m_UIMessageBoard);

	auto taskHandler = GenerateTaskHandler();

	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[0].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));
	taskScheduler->Run();

	EXPECT_CALL(*std::get<1>(taskHandler), WaitFor(m_TimeOut)).
		WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*std::get<1>(taskHandler), Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(m_UIMessageBoard, PushMessageToMessageBoard(StateMachineMap1[0].SuccessfullMessage)).Times(1);

	taskHandler = GenerateTaskHandler();
	EXPECT_CALL(*m_TaskRunnerPtrCaptured, Create(std::launch::async, StateMachineMap1[1].Task)).
		WillOnce(testing::Return(testing::ByMove(std::move(std::get<0>(taskHandler)))));

	taskScheduler->Pull(m_TimeOut);

	//When:
	taskScheduler->Stop();

	//Then:
	taskScheduler->Pull(m_TimeOut);
	taskScheduler->Pull(m_TimeOut);
	taskScheduler->Pull(m_TimeOut);
}