#pragma once

class Task
{
private:
    int time;
    int node;

public:
    Task();
    Task(int t, int n);
    void ChangeT();
    int GetTime() const;
    int GetNode() const;
};
