#pragma once
#include "task.h"
#include "tqueue.h"
#include "clamp.h"
#include <vector>
#include <iostream>
#include <algorithm>

class TaskManager
{
private:
    TQueue<Task> taskQueue;
    std::vector<Task> activeTasks;
    double freeNodes;
    double totalNodes;
    int completedTasks;
    double busyTime;
    int currentTime;
    int maxQueueSize;

public:
    TaskManager(double totalNodes, int maxQueueSize);
    void AddTask(const Task& task);
    void ExecuteStep();
    int GetPendingTasks() const;
    int GetCompletedTasks() const;
    double GetFreeNodes() const;
    double GetUtilization() const;
    double GetAverageUtilization() const;
};
