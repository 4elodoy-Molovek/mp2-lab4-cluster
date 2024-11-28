﻿#pragma once
#include <iostream>
#include "task_manager.h"
#include "cluster_ui.h"

class ClusterUI; // Forward declaration to resolve dependency

class Cluster
{
private:
    double Tmax; // Maximum runtime
    int alpha; // Probability of task generation (%)
    double N; // Total number of nodes
    int k; // Maximum tasks in the queue
    int currentTime; // Current simulation step
    TaskManager manager; // Task manager for handling tasks
    ClusterUI* ui; // Pointer to ClusterUI (avoids circular dependency)

    bool GenerateNewTask();

public:
    Cluster(double _Tmax, int _alpha, double _N, int _k);
    ~Cluster(); // Destructor to handle UI cleanup

    void ExecuteTasks();
    double GetNodeCount() const;
    double GetTotalNodes() const { return N; }
    int GetCurrentTime() const { return currentTime; }
    double GetUtilization() const { return manager.GetUtilization(); }
    int GetPendingTasks() const { return manager.GetPendingTasks(); }
    int GetCompletedTasks() const { return manager.GetCompletedTasks(); }
};