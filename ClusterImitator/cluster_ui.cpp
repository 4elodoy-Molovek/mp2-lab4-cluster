#include "cluster_ui.h"
#include "cluster.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

void ClusterUI::RenderCluster(const Cluster& c)
{
    if (!renderEnabled)
    {
        return;
    }

    // Clear the console
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence for cross-platform clearing
#endif

    int totalNodes = static_cast<int>(c.GetTotalNodes());
    int freeNodes = static_cast<int>(c.GetNodeCount());
    int usedNodes = totalNodes - freeNodes;

    int gridSize = static_cast<int>(std::ceil(std::sqrt(totalNodes)));
    int nodeCounter = 0;

    for (int i = 0; i < gridSize; ++i)
    {
        for (int j = 0; j < gridSize; ++j)
        {
            if (nodeCounter < usedNodes)
            {
                std::cout << "\033[1;31m[#]\033[0m "; // Red for used nodes
            }
            else if (nodeCounter < totalNodes)
            {
                std::cout << "\033[1;32m[#]\033[0m "; // Green for free nodes
            }
            else
            {
                std::cout << "    "; // Empty space for non-existent nodes
            }

            nodeCounter++;
        }
        std::cout << std::endl;
    }

    std::cout << "Current time: " << c.GetCurrentTime() << std::endl;
    std::cout << "Completed tasks: " << c.GetCompletedTasks() << std::endl;
    std::cout << "Pending tasks: " << c.GetPendingTasks() << std::endl;
    std::cout << "Cluster utilization: " << c.GetUtilization() << "%" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Small delay
}
