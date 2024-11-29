#include <gtest.h>
#include "tqueue.h"
#include "task.h"

class TQueueTest : public ::testing::Test
{
protected:
    TQueue<Task>* queue;

    void SetUp() override
    {
        queue = new TQueue<Task>();
    }

    void TearDown() override
    {
        delete queue;
    }
};

TEST_F(TQueueTest, INITIALIZATION_TEST_CHECKS_QUEUE_IS_EMPTY)
{
    EXPECT_TRUE(queue->IsEmpty());
}

TEST_F(TQueueTest, INITIALIZATION_TEST_CHECKS_QUEUE_SIZE)
{
    EXPECT_EQ(queue->GetSize(), 0);
}

TEST_F(TQueueTest, PUT_TASK_INCREASES_QUEUE_SIZE)
{
    Task task;
    queue->Put(task);
    EXPECT_EQ(queue->GetSize(), 1);
}

TEST_F(TQueueTest, GET_FIRST_TASK_RETURNS_CORRECT_TASK)
{
    Task task;
    queue->Put(task);
    Task retrievedTask = queue->GetFirst();
    EXPECT_EQ(retrievedTask.GetTime(), task.GetTime());
}

TEST_F(TQueueTest, REMOVE_FIRST_TASK_DECREASES_QUEUE_SIZE)
{
    Task task;
    queue->Put(task);
    queue->RemoveFirst();
    EXPECT_TRUE(queue->IsEmpty());
}

TEST_F(TQueueTest, REMOVE_FIRST_TASK_RETURNS_NO_ERROR_ON_EMPTY_QUEUE)
{
    EXPECT_NO_THROW(queue->RemoveFirst());
}

TEST_F(TQueueTest, GET_FIRST_TASK_ON_EMPTY_QUEUE_RETURNS_DEFAULT_TASK)
{
    Task defaultTask = queue->GetFirst();
    EXPECT_EQ(defaultTask.GetTime(), 0);
    EXPECT_EQ(defaultTask.GetNode(), 0);
}

TEST_F(TQueueTest, PUT_MULTIPLE_TASKS_IN_QUEUE)
{
    for (int i = 0; i < 5; ++i)
    {
        Task task;
        queue->Put(task);
    }
    EXPECT_EQ(queue->GetSize(), 5);
}

TEST_F(TQueueTest, REMOVE_FIRST_TASK_RETURNS_FIRST_ADDED_TASK)
{
    Task task1, task2;
    queue->Put(task1);
    queue->Put(task2);
    Task retrievedTask = queue->GetFirst();
    EXPECT_EQ(retrievedTask.GetTime(), task1.GetTime());
}

TEST_F(TQueueTest, IS_EMPTY_RETURNS_FALSE_AFTER_PUT)
{
    Task task;
    queue->Put(task);
    EXPECT_FALSE(queue->IsEmpty());
}

TEST_F(TQueueTest, IS_EMPTY_RETURNS_TRUE_AFTER_REMOVE)
{
    Task task;
    queue->Put(task);
    queue->RemoveFirst();
    EXPECT_TRUE(queue->IsEmpty());
}

TEST_F(TQueueTest, GET_SIZE_RETURNS_CORRECT_COUNT)
{
    EXPECT_EQ(queue->GetSize(), 0);
    Task task;
    queue->Put(task);
    EXPECT_EQ(queue->GetSize(), 1);
    queue->RemoveFirst();
    EXPECT_EQ(queue->GetSize(), 0);
}

TEST_F(TQueueTest, PUT_AND_REMOVE_TASKS_MAINTAINS_ORDER)
{
    Task task1, task2;
    queue->Put(task1);
    queue->Put(task2);
    EXPECT_EQ(queue->GetFirst().GetTime(), task1.GetTime());
    queue->RemoveFirst();
    EXPECT_EQ(queue->GetFirst().GetTime(), task2.GetTime());
}

TEST_F(TQueueTest, QUEUE_HANDLES_LARGE_NUMBER_OF_TASKS)
{
    for (int i = 0; i < 1000; ++i)
    {
        Task task;
        queue->Put(task);
    }
    EXPECT_EQ(queue->GetSize(), 1000);
}

TEST_F(TQueueTest, QUEUE_RETURNS_TO_EMPTY_STATE)
{
    for (int i = 0; i < 5; ++i)
    {
        Task task;
        queue->Put(task);
    }
    for (int i = 0; i < 5; ++i)
    {
        queue->RemoveFirst();
    }
    EXPECT_TRUE(queue->IsEmpty());
}

TEST_F(TQueueTest, GET_FIRST_TASK_RETURNS_DEFAULT_ON_EMPTY_QUEUE)
{
    Task defaultTask = queue->GetFirst();
    EXPECT_EQ(defaultTask.GetTime(), 0);
    EXPECT_EQ(defaultTask.GetNode(), 0);
}

TEST_F(TQueueTest, QUEUE_SIZE_IS_ZERO_AFTER_ALL_REMOVALS)
{
    for (int i = 0; i < 10; ++i)
    {
        Task task;
        queue->Put(task);
    }
    for (int i = 0; i < 10; ++i)
    {
        queue->RemoveFirst();
    }
    EXPECT_EQ(queue->GetSize(), 0);
}