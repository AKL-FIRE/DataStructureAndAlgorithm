//
// Created by lcy19 on 2020/2/7.
//

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include "queue.h"
#include "../Tool/utlity.h"

template <typename T>
class arrayQueue : public queue<T>{
public:
    explicit arrayQueue(long int queue_length) : queueLength(queue_length)
    {
        queueFront = -1;
        queueBack = -1;
        queueSize = 0;
        if(!make1dArray(data, queue_length))
            throw illegalParameterValue("Bad alloc.");
    }
    ~arrayQueue() override
    {delete [] data;}

    arrayQueue(const arrayQueue& queue)
    {
        queueLength = queue.queueLength;
        if(make1dArray(data, queueLength))
        {
            std::copy(queue.data, queue.data + queue.queueLength, data);
            queueFront = queue.queueFront;
            queueBack = queue.queueBack;
            queueSize = queue.queueSize;
        }
    }

    arrayQueue& operator=(const arrayQueue& queue)
    {
        if(this == &queue)
            return *this;
        // 此时对象已存在，无论大小是否为空，数组都应存在
        delete [] data;
        queueLength = queue.queueLength;
        if(make1dArray(data, queueLength))
        {
            std::copy(queue.data, queue.data + queue.queueLength, data);
            queueFront = queue.queueFront;
            queueBack = queue.queueBack;
            queueSize = queue.queueSize;
        }
        return *this;
    }

    bool empty() const override {return queueSize == 0;}
    int size() const override {return queueSize;}
    T& front() override;
    T& back() override;
    void pop() override;
    void push(const T&) override;

protected:
    int queueFront;
    int queueBack;
    long int queueLength;
    int queueSize;
    T* data;
};

template <typename T>
T& arrayQueue<T>::front()
{
    if(empty())
        throw illegalParameterValue("The queue is empty.");
    return data[(queueFront + 1) % queueLength];
}

template <typename T>
T& arrayQueue<T>::back()
{
    if(empty())
        throw illegalParameterValue("The queue is empty.");
    return data[queueBack % queueLength];
}

template <typename T>
void arrayQueue<T>::push(const T& theElement)
{
    if((queueBack + 1) % queueLength == queueFront)
    {
        T* newQueue = new T[2 * queueLength];

        // 复制原来的元素
        int start = (queueFront + 1) % queueLength;
        if(start < 2) // 无环
            std::copy(data + start, data + start + queueLength - 1, newQueue);
        else // 有环
        {
            std::copy(data + start, data + queueLength, newQueue);
            std::copy(data, data + (queueFront % queueLength) + 1, newQueue + queueLength - start);
        }
        // 设置位置
        queueFront = 2 * queueLength - 1;
        queueBack = queueSize - 1;
        queueLength *= 2;
        delete [] data;
        data = newQueue;
    }

    queueBack = (queueBack + 1) % queueLength;
    data[queueBack] = theElement;
    queueSize++;
}

template <typename T>
void arrayQueue<T>::pop()
{
    if(empty())
        throw illegalParameterValue("The queue is empty.");
    queueFront = (queueFront + 1) % queueLength;
    data[queueFront].~T();
    queueSize--;
}
#endif //ARRAYQUEUE_H
