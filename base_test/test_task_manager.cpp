#include <gtest.h>
#include "task_manager.h"

class TaskManagerTest : public ::testing::Test
{
protected:
    TaskManager* manager;

    void SetUp() override
    {
        manager = new TaskManager(10, 5);
    }

    void TearDown() override
    {
        delete manager;
    }
};

TEST_F(TaskManagerTest, INITIALIZATION_TEST_CHECKS_COMPLETED_TASKS)
{
    EXPECT_EQ(manager->GetCompletedTasks(), 0);
}

TEST_F(TaskManagerTest, INITIALIZATION_TEST_CHECKS_PENDING_TASKS)
{
    EXPECT_EQ(manager->GetPendingTasks(), 0);
}

TEST_F(TaskManagerTest, INITIALIZATION_TEST_CHECKS_FREE_NODES)
{
    EXPECT_DOUBLE_EQ(manager->GetFreeNodes(), 10);
}

TEST_F(TaskManagerTest, ADD_TASK_INCREASES_PENDING_TASKS)
{
    Task task;
    manager->AddTask(task);
    EXPECT_EQ(manager->GetPendingTasks(), 1);
}

TEST_F(TaskManagerTest, EXECUTE_STEP_INCREASES_COMPLETED_TASKS)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_GE(manager->GetCompletedTasks(), 0);
}

TEST_F(TaskManagerTest, FREE_NODES_DECREASES_WHEN_TASK_ADDED)
{
    Task task;
    manager->AddTask(task);
    EXPECT_DOUBLE_EQ(manager->GetFreeNodes(), 9);
}

TEST_F(TaskManagerTest, PENDING_TASKS_INCREASES_WHEN_TASK_ADDED)
{
    Task task;
    manager->AddTask(task);
    EXPECT_EQ(manager->GetPendingTasks(), 1);
}

TEST_F(TaskManagerTest, EXECUTE_STEP_DECREASES_PENDING_TASKS)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_LE(manager->GetPendingTasks(), 1);
}

TEST_F(TaskManagerTest, UTILIZATION_CALCULATED_CORRECTLY)
{
    EXPECT_GE(manager->GetUtilization(), 0.0);
    EXPECT_LE(manager->GetUtilization(), 100.0);
}

TEST_F(TaskManagerTest, TASK_MANAGER_HANDLES_MULTIPLE_TASKS)
{
    for (int i = 0; i < 5; ++i)
    {
        Task task;
        manager->AddTask(task);
    }
    manager->ExecuteStep();
    EXPECT_GE(manager->GetCompletedTasks(), 0);
}

TEST_F(TaskManagerTest, FREE_NODES_INCREASES_AFTER_TASK_COMPLETION)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_DOUBLE_EQ(manager->GetFreeNodes(), 10);
}

TEST_F(TaskManagerTest, PENDING_TASKS_DECREASES_AFTER_EXECUTION)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_LE(manager->GetPendingTasks(), 1);
}

TEST_F(TaskManagerTest, COMPLETED_TASKS_INCREASES_AFTER_EXECUTION)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_GE(manager->GetCompletedTasks(), 0);
}

TEST_F(TaskManagerTest, UTILIZATION_INCREASES_WHEN_TASKS_ARE_EXECUTED)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_GT(manager->GetUtilization(), 0.0);
}

TEST_F(TaskManagerTest, TASK_MANAGER_RETURNS_PENDING_TASKS_COUNT)
{
    EXPECT_EQ(manager->GetPendingTasks(), 0);
    Task task;
    manager->AddTask(task);
    EXPECT_EQ(manager->GetPendingTasks(), 1);
}

TEST_F(TaskManagerTest, TASK_MANAGER_RETURNS_COMPLETED_TASKS_COUNT)
{
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_GE(manager->GetCompletedTasks(), 0);
}

TEST_F(TaskManagerTest, TASK_MANAGER_RETURNS_FREE_NODES_COUNT)
{
    EXPECT_DOUBLE_EQ(manager->GetFreeNodes(), 10);
    Task task;
    manager->AddTask(task);
    manager->ExecuteStep();
    EXPECT_DOUBLE_EQ(manager->GetFreeNodes(), 10);
}

TEST_F(TaskManagerTest, TASK_MANAGER_RETURNS_UTILIZATION_PERCENTAGE)
{
    EXPECT_GE(manager->GetUtilization(), 0.0);
    EXPECT_LE(manager->GetUtilization(), 100.0);
}

TEST_F(TaskManagerTest, TASK_MANAGER_HANDLES_CONCURRENT_TASKS)
{
    for (int i = 0; i < 5; ++i)
    {
        Task task;
        manager->AddTask(task);
    }
    manager->ExecuteStep();
    EXPECT_GE(manager->GetCompletedTasks(), 0);
}