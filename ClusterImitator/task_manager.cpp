#include "task_manager.h"

TaskManager::TaskManager(double _totalNodes, int _maxQueueSize)
{
    freeNodes = _totalNodes;
    totalNodes = _totalNodes;
    completedTasks = 0;
    busyTime = 0;
    currentTime = 0;
    maxQueueSize = _maxQueueSize;
}

void TaskManager::AddTask(const Task& task)
{
    if (taskQueue.GetSize() < maxQueueSize)
    {
        taskQueue.Put(task);
    }
    else
    {
        std::cout << "Task queue is full. Cannot add new task." << std::endl;
    }
}

void TaskManager::ExecuteStep()
{
    for (size_t i = 0; i < activeTasks.size();)
    {
        activeTasks[i].ChangeT();

        if (activeTasks[i].GetTime() == 0)
        {
            freeNodes += activeTasks[i].GetNode();
            activeTasks.erase(activeTasks.begin() + i);
            ++completedTasks;
        }
        else
        {
            ++i;
        }
    }

    while (!taskQueue.IsEmpty() && taskQueue.GetFirst().GetNode() <= freeNodes)
    {
        Task task = taskQueue.GetFirst();
        freeNodes -= task.GetNode();
        activeTasks.push_back(task);
        taskQueue.RemoveFirst();
    }

    busyTime += (totalNodes - freeNodes) / totalNodes;
    ++currentTime;
}

int TaskManager::GetPendingTasks() const
{
    return taskQueue.GetSize() + activeTasks.size();
}

int TaskManager::GetCompletedTasks() const
{
    return completedTasks;
}

double TaskManager::GetFreeNodes() const
{
    return freeNodes;
}

double TaskManager::GetUtilization() const
{
    return (busyTime / currentTime) * 100;
}