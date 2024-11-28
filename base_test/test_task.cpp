#include <gtest.h>
#include <algorithm>
#include "task.h"

class TaskTest : public ::testing::Test
{
protected:
    Task* task;
    void SetUp() override
    {
        task = new Task();
    }
    void TearDown() override
    {
        delete task;
    }
};

TEST_F(TaskTest, CONSTRUCTOR_CREATES_TASK_WITH_VALID_TIME)
{
    EXPECT_GE(task->GetTime(), 1);
    EXPECT_LE(task->GetTime(), 10);
}

TEST_F(TaskTest, CONSTRUCTOR_CREATES_TASK_WITH_VALID_NODES)
{
    EXPECT_GE(task->GetNode(), 1);
    EXPECT_LE(task->GetNode(), 3);
}

TEST_F(TaskTest, CHANGE_TIME_DECREMENTS_TIME_CORRECTLY)
{
    int initialTime = task->GetTime();
    task->ChangeT();
    EXPECT_EQ(task->GetTime(), initialTime - 1);
}

TEST_F(TaskTest, CHANGE_TIME_PREVENTS_NEGATIVE_TIME)
{
    for (int i = 0; i < 20; ++i)
    {
        task->ChangeT();
    }
    EXPECT_EQ(task->GetTime(), 0);
}

TEST_F(TaskTest, GET_TIME_RETURNS_CORRECT_INITIAL_VALUE)
{
    int time = task->GetTime();
    EXPECT_TRUE(time >= 1 && time <= 10);
}

TEST_F(TaskTest, GET_NODE_RETURNS_CORRECT_INITIAL_VALUE)
{
    int node = task->GetNode();
    EXPECT_TRUE(node >= 1 && node <= 3);
}

TEST_F(TaskTest, MULTIPLE_TASKS_HAVE_DIFFERENT_PARAMETERS)
{
    Task task1, task2;
    EXPECT_FALSE((task1.GetTime() == task2.GetTime()) &&
        (task1.GetNode() == task2.GetNode()));
}

TEST_F(TaskTest, TIME_CHANGES_MONOTONICALLY_DECREASING)
{
    int initialTime = task->GetTime();
    for (int i = 0; i < 5; ++i)
    {
        int prevTime = task->GetTime();
        task->ChangeT();
        EXPECT_LE(task->GetTime(), prevTime);
    }
}

TEST_F(TaskTest, RANDOM_TASK_GENERATION_DISTRIBUTION)
{
    std::vector<int> times, nodes;
    for (int i = 0; i < 1000; ++i)
    {
        Task randomTask;
        times.push_back(randomTask.GetTime());
        nodes.push_back(randomTask.GetNode());
    }

    // Проверка распределения времени
    int minTime = *std::min_element(times.begin(), times.end());
    int maxTime = *std::max_element(times.begin(), times.end());
    EXPECT_GE(minTime, 1);
    EXPECT_LE(maxTime, 10);

    // Проверка распределения узлов
    int minNode = *std::min_element(nodes.begin(), nodes.end());
    int maxNode = *std::max_element(nodes.begin(), nodes.end());
    EXPECT_GE(minNode, 1);
    EXPECT_LE(maxNode, 3);
}

TEST_F(TaskTest, TASK_TIME_ZERO_AFTER_COMPLETE_EXECUTION)
{
    while (task->GetTime() > 0)
    {
        task->ChangeT();
    }
    EXPECT_EQ(task->GetTime(), 0);
}

TEST_F(TaskTest, DIFFERENT_TASKS_HAVE_UNIQUE_CHARACTERISTICS)
{
    Task task1, task2, task3;
    std::set<std::pair<int, int>> uniqueTasks;

    uniqueTasks.insert({ task1.GetTime(), task1.GetNode() });
    uniqueTasks.insert({ task2.GetTime(), task2.GetNode() });
    uniqueTasks.insert({ task3.GetTime(), task3.GetNode() });

    EXPECT_GE(uniqueTasks.size(), 2);
}

TEST_F(TaskTest, TASK_TIME_WITHIN_REASONABLE_RANGE)
{
    EXPECT_TRUE(task->GetTime() > 0 && task->GetTime() <= 10);
}

TEST_F(TaskTest, TASK_NODE_WITHIN_REASONABLE_RANGE)
{
    EXPECT_TRUE(task->GetNode() > 0 && task->GetNode() <= 3);
}

TEST_F(TaskTest, CHANGE_TIME_DOES_NOT_MODIFY_NODE)
{
    int initialNode = task->GetNode();
    for (int i = 0; i < 5; ++i)
    {
        task->ChangeT();
        EXPECT_EQ(task->GetNode(), initialNode);
    }
}

TEST_F(TaskTest, TASK_HAS_CONSISTENT_INTERNAL_STATE)
{
    int time = task->GetTime();
    int node = task->GetNode();

    task->ChangeT();
    EXPECT_EQ(task->GetNode(), node);
    EXPECT_EQ(task->GetTime(), time - 1);
}

TEST_F(TaskTest, TASK_ATTRIBUTES_ARE_IMMUTABLE_AFTER_CREATION)
{
    int initialTime = task->GetTime();
    int initialNode = task->GetNode();

    task->ChangeT();
    EXPECT_EQ(task->GetNode(), initialNode);
}

TEST_F(TaskTest, TASK_CREATION_IS_DETERMINISTIC)
{
    Task task1, task2;
    EXPECT_TRUE(task1.GetTime() > 0 && task1.GetTime() <= 10);
    EXPECT_TRUE(task2.GetTime() > 0 && task2.GetTime() <= 10);
}

TEST_F(TaskTest, TASK_RESOURCES_ARE_CONSISTENT)
{
    EXPECT_TRUE(task->GetTime() >= task->GetNode());
}

TEST_F(TaskTest, TASK_DECREMENTS_CORRECTLY_MULTIPLE_TIMES)
{
    int initialTime = task->GetTime();
    for (int i = 0; i < initialTime; ++i)
    {
        task->ChangeT();
        EXPECT_EQ(task->GetTime(), initialTime - i - 1);
    }
}

TEST_F(TaskTest, TASK_FINAL_STATE_IS_ZERO)
{
    while (task->GetTime() > 0)
    {
        task->ChangeT();
    }
    EXPECT_EQ(task->GetTime(), 0);
}