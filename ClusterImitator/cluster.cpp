#include "cluster.h"

Cluster::Cluster(double _Tmax, int _alpha, double _N, int _k, bool testing) :
    Tmax(_Tmax), alpha(_alpha), N(_N), k(_k),
    manager(_N, _k),
    currentTime(0),
    renderEnabled(!testing),
    isTesting(testing)
{
    ui = new ClusterUI();
    ui->EnableRendering(!testing); // Disable rendering in testing mode
}

Cluster::~Cluster()
{
    delete ui; // Clean up UI 
}

bool Cluster::GenerateNewTask()
{
    return (rand() % 100) < alpha;
}

void Cluster::EnableRendering(bool enable)
{
    renderEnabled = enable;
    ui->EnableRendering(enable);
}

void Cluster::SetTestingMode(bool testing)
{
    isTesting = testing;
    EnableRendering(!testing); // Disable rendering if in testing mode
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

        if (renderEnabled)
        {
            ui->RenderCluster(*this);
        }

        currentTime++;
    }
}

double Cluster::GetNodeCount() const
{
    return manager.GetFreeNodes();
}

std::ostream& operator<<(std::ostream& out, const Cluster& c)
{
    out << "Cluster statistics:\n"
        << "Total runtime: " << c.currentTime << '\n'
        << "Completed tasks: " << c.manager.GetCompletedTasks() << '\n'
        << "Pending tasks: " << c.manager.GetPendingTasks() << '\n'
        << "Cluster utilization: " << c.manager.GetUtilization() << "%\n";
    return out;
}
