//
//  utlity.h
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 23/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef utlity_h
#define utlity_h

#include "../Exception/Exception.hpp"
#include <algorithm>

template <typename T>
bool make1dArray(T *&x, int size)
{
    try {
        x = new T[size];
        return true;
    } catch (std::bad_alloc) {
        return false;
    }
}

template <typename T>
void changeLength1D(T *&a, int oldLength, int newLength)
{
    if(newLength < 0)
        throw illegalParameterValue("new length must be >= 0");
    T *temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

template <typename T>
bool make2dArray(T **&x, int numberOfRows, int numberOfColumns)
{
    try {
        x = new T*[numberOfRows];
        
        for(int i = 0; i < numberOfRows; i++)
            x[i] = new int[numberOfColumns];
        return true;
    } catch (std::bad_alloc) {
       return false;
    }
}

#endif /* utlity_h */
