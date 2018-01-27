//
//  arrayStack.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 27/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef arrayStack_hpp
#define arrayStack_hpp

#include "stack.hpp"

template <typename T>
class arrayStack : public stack<T>
{
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() {delete [] stack;}
    bool empty() const {return stackTop == -1;}
    int size() const {return stackTop + 1;}
    T& top()
    {
        if(stackTop == -1)
            throw illegalParameterValue("The stack is empty.");
        return stack[stackTop];
    }
    void pop()
    {
        if(stackTop == -1)
            throw illegalParameterValue("The stack is empty.");
        stack[stackTop--].~T();
    }
    void push(const T &theElement);
    friend std::ostream& operator<<(std::ostream &out, arrayStack<T> &e)
    {
        for(int i = 0; i <= e.stackTop; i++)
            std::cout << e.stack[i] << " ";
        return out;
    }
private:
    int stackTop;
    int arrayLength;
    T *stack;
};

template <typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::strstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template <typename T>
void arrayStack<T>::push(const T &theElement)
{
    if(stackTop == arrayLength - 1)
    {
        changeLength1D(stack, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement;
}

#endif /* arrayStack_hpp */
