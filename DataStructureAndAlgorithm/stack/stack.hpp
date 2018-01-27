//
//  stack.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 27/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include "../Tool/utlity.h"

template <typename T>
class stack
{
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T &theElement) = 0;
};

#endif /* stack_hpp */
