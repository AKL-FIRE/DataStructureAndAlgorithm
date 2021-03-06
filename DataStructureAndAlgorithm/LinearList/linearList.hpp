//
//  linearList.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 23/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef linearList_hpp
#define linearList_hpp

#include <iostream>
#include <iterator>
#include "../Tool/utlity.h"

template <typename T>
class linearList
{
public:
    virtual ~linearList() = default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(std::ostream &out) const = 0;
};

#endif /* linearList_hpp */
