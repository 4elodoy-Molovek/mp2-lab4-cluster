#pragma once
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
    bool renderEnabled; // Flag to control rendering
    bool isTesting; // Flag for testing mode

    bool GenerateNewTask();

public:
    Cluster(double _Tmax, int _alpha, double _N, int _k, bool testing = false);
    ~Cluster(); // Destructor to handle UI cleanup

    void ExecuteTasks();
    void EnableRendering(bool enable = true);
    void SetTestingMode(bool testing);
    double GetNodeCount() const;
    double GetTotalNodes() const { return N; }
    int GetCurrentTime() const { return currentTime; }
    double GetUtilization() const { return manager.GetUtilization(); }
    int GetPendingTasks() const { return manager.GetPendingTasks(); }
    int GetCompletedTasks() const { return manager.GetCompletedTasks(); }

    friend std::ostream& operator<<(std::ostream& out, const Cluster& c);
};
