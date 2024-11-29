#pragma once
#include <vector>

template <typename T>
class TQueue
{
private:
    std::vector<T> queue;

public:
    void Put(const T& task);
    void RemoveFirst();
    T GetFirst() const;
    bool IsEmpty() const;
    size_t GetSize() const;
};

template <typename T>
void TQueue<T>::Put(const T& task)
{
    queue.push_back(task);
}

template <typename T>
void TQueue<T>::RemoveFirst()
{
    if (!queue.empty())
    {
        queue.erase(queue.begin());
    }
}

template <typename T>
T TQueue<T>::GetFirst() const
{
    return queue.empty() ? T(0, 0) : queue.front();
}

template <typename T>
bool TQueue<T>::IsEmpty() const
{
    return queue.empty();
}

template <typename T>
size_t TQueue<T>::GetSize() const
{
    return queue.size();
}
