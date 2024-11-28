#pragma once

class Task
{
private:
    int time; // Time required to complete the task
    int node; // Number of nodes required

public:
    Task();
    void ChangeT();
    int GetTime() const;
    int GetNode() const;
};