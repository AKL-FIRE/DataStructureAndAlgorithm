//
//  extendeLinearList.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 24/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef extendeLinearList_hpp
#define extendeLinearList_hpp

#include "linearList.hpp"

template <typename T>
class extendedLinearList : virtual public linearList<T>
{
public:
    virtual ~extendedLinearList() {}
    virtual void clear() = 0;
    virtual void push_back(const T &theElement) = 0;
};

#endif /* extendeLinearList_hpp */
