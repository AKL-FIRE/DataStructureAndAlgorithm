//
//  derivedArrayStack.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 27/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef derivedArrayStack_hpp
#define derivedArrayStack_hpp

#include "stack.hpp"
#include "../LinearList/arrayList.hpp"

template <typename T>
class derivedArrayStack : private arrayList<T>, public stack<T>
{
public:
    derivedArrayStack(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}
    bool empty() const {return arrayList<T>::empty();}
    int size() const {return arrayList<T>::size();}
    T& top()
    {
        if(arrayList<T>::empty())
            throw illegalParameterValue("The stack is empty.");
        return this->get(arrayList<T>::size() - 1);
    }
    void pop()
    {
        if(arrayList<T>::empty())
            throw illegalParameterValue("The stack is empty.");
        this->erase(arrayList<T>::size() - 1);
    }
    void push(const T &theElement)
    {
        this->insert(arrayList<T>::size(), theElement);
    }
    friend std::ostream& operator<<(std::ostream &out, derivedArrayStack<T> &e)
    {
        e.output(out);
        return out;
    }
};

#endif /* derivedArrayStack_hpp */
