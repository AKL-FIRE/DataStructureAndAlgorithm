//
//  linkedStack.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 27/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef linkedStack_hpp
#define linkedStack_hpp

#include "stack.hpp"

template <typename T>
struct chainNode
{
    T element;
    chainNode<T>* next;
    
    chainNode() {}
    chainNode(const T &element) {this->element = element;}
    chainNode(const T &element, chainNode<T> *next) {this->element = element; this->next = next;}
};

template <typename T>
class linkedStack : public stack<T>
{
public:
    linkedStack(int initialCapacity = 10) {stackTop = nullptr; stackSize = 0;}
    ~linkedStack();
    bool empty() const {return stackSize == 0;}
    int size() const {return stackSize;}
    T& top()
    {
        if(stackSize == 0)
            throw illegalParameterValue("The stack is empty.");
        return stackTop->element;
    }
    void pop();
    void push(const T &theElement)
    {
        stackTop = new chainNode<T>(theElement,stackTop);
        stackSize++;
    }
    friend std::ostream& operator<<(std::ostream &out, linkedStack<T> &e)
    {
        chainNode<T> *p = e.stackTop;
        while(p != nullptr)
        {
            std::cout << p->element << " ";
            p = p->next;
        }
        return out;
    }
private:
    chainNode<T> *stackTop;
    int stackSize;
};

template <typename T>
linkedStack<T>::~linkedStack()
{
    while(stackTop != nullptr)
    {
        chainNode<T> *nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
    }
}

template <typename T>
void linkedStack<T>::pop()
{
    if(stackSize == 0)
        throw illegalParameterValue("The stack is empty.");
    chainNode<T> *nextnode = stackTop->next;
    delete stackTop;
    stackTop = nextnode;
    stackSize--;
}

#endif /* linkedStack_hpp */
