#include "cluster_ui.h"
#include "cluster.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

void ClusterUI::RenderCluster(const Cluster& c)
{
    system("cls"); // Очистка консоли

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
                std::cout << "\033[1;31m[#]\033[0m "; // Красный для используемых узлов
            }
            else if (nodeCounter < totalNodes)
            {
                std::cout << "\033[1;32m[#]\033[0m "; // Зеленый для свободных узлов
            }
            else
            {
                std::cout << "    "; // Пустое место для несуществующих узлов
            }

            nodeCounter++;
        }
        std::cout << std::endl;
    }

    std::cout << "Current time: " << c.GetCurrentTime() << std::endl;
    std::cout << "Completed tasks: " << c.GetCompletedTasks() << std::endl;
    std::cout << "Pending tasks: " << c.GetPendingTasks() << std::endl;
    std::cout << "Cluster utilization: " << c.GetUtilization() << "%" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Фиксированная задержка в 1 секунду
}