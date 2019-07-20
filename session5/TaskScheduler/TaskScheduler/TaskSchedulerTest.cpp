#include <chrono>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MockTask.h"
#include "TaskScheduler.h"
#include "MockUIMessageBoard.h"
#include "MockTaskRunner.h"
#include "MockTaskHandle.h"

using namespace std::chrono_literals;

class TaskSchedulerTest : public testing::Test
{

protected:
	void SetUp() override
	{
		m_StateMachineMap.push_back({ m_Task0, "Task0SuccessfullDescription", "Task0FailureDescription", 1, TaskScheduler::InitialState });
		m_StateMachineMap.push_back({ m_Task1, "Task1SuccessfullDescription", "Task1FailureDescription", 2, TaskScheduler::InitialState });
		m_StateMachineMap.push_back({ m_Task2, "Task2SuccessfullDescription", "Task2FailureDescription", 3, TaskScheduler::InitialState });
		m_StateMachineMap.push_back({ m_Task3, "Task3SuccessfullDescription", "Task3FailureDescription", TaskScheduler::InitialState, TaskScheduler::InitialState });
	}

	std::shared_ptr<MockTask> m_Task0 = std::make_shared<MockTask>();
	std::shared_ptr<MockTask> m_Task1 = std::make_shared<MockTask>();
	std::shared_ptr<MockTask> m_Task2 = std::make_shared<MockTask>();
	std::shared_ptr<MockTask> m_Task3 = std::make_shared<MockTask>();
	
	std::vector<TaskScheduler::State> m_StateMachineMap;
	std::shared_ptr<MockUIMessageBoard> m_MessageBoard = std::make_shared<MockUIMessageBoard>();
	std::shared_ptr<MockTaskRunner> m_TaskRunner = std::make_shared<MockTaskRunner>();
	std::shared_ptr<MockTaskHandle> m_TaskHandle = std::make_shared<MockTaskHandle>();

};

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

TEST_F(TaskSchedulerTest, GivenAStateMachineMapAndATaskSchedulerConstructedWithItWhenRunIsCalledThenFirstTaskMustBeRun)
{
	auto taskScheduler = std::make_unique<TaskScheduler>(m_StateMachineMap, m_MessageBoard, m_TaskRunner);
	
	EXPECT_CALL(*m_TaskRunner, RunAsync(testing::Eq(m_Task0))).WillOnce(testing::Return(m_TaskHandle));

	taskScheduler->Run();
}

//initial->Task0->S->Task1->S->Task2->F->initial
TEST_F(TaskSchedulerTest, GivenAStateMachineMapWhenPullIsCalledThenExpectedScenarioMustBeRun)
{
	auto taskScheduler = std::make_unique<TaskScheduler>(m_StateMachineMap, m_MessageBoard, m_TaskRunner);

	EXPECT_CALL(*m_TaskRunner, RunAsync(testing::Eq(m_Task0))).WillOnce(testing::Return(m_TaskHandle));

	taskScheduler->Run();

	EXPECT_CALL(*m_TaskHandle, WaitFor(testing::Eq(100ms))).WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*m_TaskHandle, Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(*m_MessageBoard, PushMessageToBoard(testing::Eq(m_StateMachineMap[0].DescriptionOnSuccessfull)));
	EXPECT_CALL(*m_TaskRunner, RunAsync(testing::Eq(m_Task1))).WillOnce(testing::Return(m_TaskHandle));
	taskScheduler->Pull(100ms);

	EXPECT_CALL(*m_TaskHandle, WaitFor(testing::Eq(100ms))).WillOnce(testing::Return(std::future_status::timeout));
	taskScheduler->Pull(100ms);

	EXPECT_CALL(*m_TaskHandle, WaitFor(testing::Eq(100ms))).WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*m_TaskHandle, Get()).WillOnce(testing::Return(true));
	EXPECT_CALL(*m_MessageBoard, PushMessageToBoard(testing::Eq(m_StateMachineMap[1].DescriptionOnSuccessfull)));
	EXPECT_CALL(*m_TaskRunner, RunAsync(testing::Eq(m_Task2))).WillOnce(testing::Return(m_TaskHandle));
	taskScheduler->Pull(100ms);

	EXPECT_CALL(*m_TaskHandle, WaitFor(testing::Eq(100ms))).WillOnce(testing::Return(std::future_status::ready));
	EXPECT_CALL(*m_TaskHandle, Get()).WillOnce(testing::Return(false));
	EXPECT_CALL(*m_MessageBoard, PushMessageToBoard(testing::Eq(m_StateMachineMap[2].DescriptionOnFailure)));
	taskScheduler->Pull(100ms);

	taskScheduler->Pull(100ms);
	taskScheduler->Pull(100ms);
	taskScheduler->Pull(100ms);
	taskScheduler->Pull(100ms);
	taskScheduler->Pull(100ms);
	taskScheduler->Pull(100ms);
}

TEST_F(TaskSchedulerTest, GivenAStateMachineMapWhenRunIsCalledTwiceThenSecondCallMsutBeIgnored)
{
	auto taskScheduler = std::make_unique<TaskScheduler>(m_StateMachineMap, m_MessageBoard, m_TaskRunner);

	EXPECT_CALL(*m_TaskRunner, RunAsync(testing::Eq(m_Task0))).WillOnce(testing::Return(m_TaskHandle));

	taskScheduler->Run();
	taskScheduler->Run();
}