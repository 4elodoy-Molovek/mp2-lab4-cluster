#pragma once
#include "task.h"
#include "tqueue.h"
#include <vector>
#include <iostream>

class TaskManager
{
private:
    TQueue<Task> taskQueue; // Queue of tasks
    std::vector<Task> activeTasks; // Currently executing tasks
    double freeNodes; // Available cluster nodes
    double totalNodes; // Total cluster nodes
    int completedTasks; // Number of completed tasks
    double busyTime; // Time spent busy
    int currentTime; // Current time step
    int maxQueueSize; // Maximum number of tasks in the queue

public:
    TaskManager(double totalNodes, int maxQueueSize);
    void AddTask(const Task& task); // Add a new task to the queue
    void ExecuteStep(); // Execute one time step
    int GetPendingTasks() const; // Get count of pending tasks
    int GetCompletedTasks() const; // Get count of completed tasks
    double GetFreeNodes() const; // Get count of free nodes
    double GetUtilization() const; // Get utilization percentage
};