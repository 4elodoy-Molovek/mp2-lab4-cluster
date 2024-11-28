#include "cluster.h"

Cluster::Cluster(double _Tmax, int _alpha, double _N, int _k) :
    Tmax(_Tmax), alpha(_alpha), N(_N), k(_k), manager(_N, _k), currentTime(0)
{
    ui = new ClusterUI();
}

Cluster::~Cluster()
{
    delete ui; // Clean up UI 
}

bool Cluster::GenerateNewTask()
{
    return (rand() % 100) < alpha;
}

void Cluster::ExecuteTasks()
{
    for (int t = 0; t < Tmax; ++t)
    {
        int newTasksCount = 0;
        for (int i = 0; i < k && newTasksCount < k; ++i)
        {
            if (GenerateNewTask())
            {
                Task newTask;
                manager.AddTask(newTask);
                newTasksCount++;
            }
        }

        manager.ExecuteStep();
        ui->RenderCluster(*this);
        currentTime++;
    }
}

double Cluster::GetNodeCount() const
{
    return manager.GetFreeNodes();
}

std::ostream& operator<<(std::ostream& out, const Cluster& c)
{
    out << "Cluster Final Statistics:\n"
        << "Total runtime: " << c.currentTime << " time units\n"
        << "Completed tasks: " << c.manager.GetCompletedTasks() << "\n"
        << "Unfinished tasks: " << c.manager.GetPendingTasks() << "\n"
        << "Average cluster utilization: " << c.manager.GetAverageUtilization() << "%\n";
    return out;
}
