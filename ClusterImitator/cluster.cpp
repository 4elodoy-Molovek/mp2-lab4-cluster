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
        for (int i = 0; i < k; ++i)
        {
            if (GenerateNewTask())
            {
                Task newTask;
                manager.AddTask(newTask);
            }
        }

        manager.ExecuteStep();
        ui->RenderCluster(*this);
        currentTime++;
    }

    // Вывод статистики после завершения работы кластера
    std::cout << "Final statistics:\n";
    std::cout << "Total completed tasks: " << manager.GetCompletedTasks() << '\n';
    std::cout << "Total pending tasks: " << manager.GetPendingTasks() << '\n';
    std::cout << "Average cluster utilization: " << manager.GetUtilization() << "%\n";
}

double Cluster::GetNodeCount() const
{
    return manager.GetFreeNodes();
}
