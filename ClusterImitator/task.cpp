#include "task.h"
#include <cstdlib>

Task::Task()
{
    time = rand() % 10 + 1;
    node = rand() % 3 + 1;
}

Task::Task(int t, int n)
{
    time = t;
    node = n;
}

void Task::ChangeT()
{
    if (time > 0)
    {
        --time;
    }
}

int Task::GetTime() const
{
    return time;
}

int Task::GetNode() const
{
    return node;
}
