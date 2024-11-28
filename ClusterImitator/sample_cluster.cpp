#include "cluster.h"
#include <iostream>
#include <cstdlib>
#include <locale>

int main()
{
    system("chcp 65001");
    system("cls");

    double Tmax, N;
    int alpha, k;

    std::cout << "Enter the maximum cluster runtime: ";
    std::cin >> Tmax;

    std::cout << "Enter the probability of a new task appearing (%): ";
    std::cin >> alpha;

    std::cout << "Enter the number of computing nodes: ";
    std::cin >> N;

    std::cout << "Enter the maximum number of tasks in the queue: ";
    std::cin >> k;

    Cluster cluster(Tmax, alpha, N, k);
    cluster.ExecuteTasks();
    std::cout << std::endl << cluster;

    return 0;
}