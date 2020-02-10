//
// Created by lcy19 on 2020/2/9.
//

#ifndef SORT_H
#define SORT_H

#include <iterator>

// 1.Selection Sort
// Time complexity: O(n^2)
// Space complexity: O(1)
// unstable sort
// in-place sort
template <typename _RandomAccessIterator, typename _Compare>
void selectSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    auto _distance = _last - _first;
    for(decltype(_distance) i = 0; i < _distance - 1; ++i)
    {
        decltype(_distance) minMax = i;
        for(decltype(_distance) j = i + 1; j < _distance; ++j)
        {
            if(_comp(*(_first + j), *(_first + minMax)))
                minMax = j;
        }
        std::swap(*(_first + i), *(_first + minMax));
    }
}

// 2.Insertion Sort
// Time complexity: O(n^2)
// Space complexity: O(1)
// stable sort
// in-place sort
template <typename _RandomAccessIterator, typename _Compare>
void insertSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    using _value_type = typename std::iterator_traits<_RandomAccessIterator>::value_type;
    auto _distance = _last - _first;
    for(decltype(_distance) i = 1; i < _distance; ++i)
    {
        _value_type current_value = *(_first + i);
        decltype(_distance) j = i - 1;
        while(j >= 0 && !_comp(*(_first + j), current_value))
        {
            *(_first + j + 1) = *(_first + j);
            j--;
        }
        *(_first + j + 1) = current_value;
    }
}

// 2.Bubble Sort
// Time complexity: O(n^2)
// Space complexity: O(1)
// stable sort
// in-place sort
template <typename _RandomAccessIterator, typename _Compare>
void bubbleSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    auto _distance = _last - _first;
    for(decltype(_distance) i = 0; i < _distance; ++i)
    {
        bool finish = true;
        for(decltype(_distance) j = 0; j < _distance - i - 1; ++j)
        {
            if(_comp(*(_first + j + 1), *(_first + j))) {
                finish = false;
                std::swap(*(_first + j), *(_first + j + 1));
            }
        }
        if(finish)
            break;
    }
}
#endif //SORT_H
