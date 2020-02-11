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

// 3.Bubble Sort
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

// 4.Shell Sort
// Time complexity: O(nlogn)
// Space complexity: O(1)
// unstable sort
// in-place sort
template <typename _RandomAccessIterator, typename _Distance, typename _Compare>
void _shellSort(_RandomAccessIterator _first, _Distance _gap, _Distance i, _Compare _comp)
{
    using _value_type = typename std::iterator_traits<_RandomAccessIterator>::value_type;
    _value_type temp = *(_first + i);
    decltype(_gap) j;
    for(j = i - _gap; j >= 0; j -= _gap)
    {
        if(!_comp(*(_first + j), temp))
            *(_first + j + _gap) = *(_first + j);
        else
            break;
    }
    *(_first + j + _gap) = temp;
}

template <typename _RandomAccessIterator, typename _Compare>
void shellSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    auto _distance = _last - _first;
    for(auto gap = _distance / 2; gap > 0; gap /= 2)
    {
        for(auto i = gap; i < _distance; ++i)
            _shellSort(_first, gap, i, _comp);
    }
}

// 5.BottomUp Sort and Merge Sort
// Time complexity: O(nlogn)
// Space complexity: O(n)
// stable sort
// out-place sort
template <typename _RandomAccessIterator, typename _Compare>
void _mergeSortedLists(_RandomAccessIterator _p, _RandomAccessIterator _q, _RandomAccessIterator _r, _Compare _comp)
{
    // _p, _q, _r point to the subarray A[p...q] A[q+1...r]
    auto size1 = _q - _p + 1;
    auto size2 = _r - (_q + 1) + 1;
    using _value_type = typename std::iterator_traits<_RandomAccessIterator>::value_type;
    _value_type *temp = new _value_type[size1 + size2];
    _RandomAccessIterator s = _p, t = _q + 1;
    _value_type* k = temp;
    while(s - _q <= 0 && t - _r <= 0)
    {
        if(_comp(*s, *t))
        {
            *k = *s;
            s++;
        }else
        {
            *k = *t;
            t++;
        }
        k++;
    }
    if(s == _q + 1)
        std::copy(t, _r + 1, k);
    else
        std::copy(s, _q + 1, k);
    std::copy(temp, temp + size1 + size2, _p);
    delete [] temp;
}

template <typename _RandomAccessIterator, typename _Compare>
void bottomUpSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    using _Distance_type = typename std::iterator_traits<_RandomAccessIterator>::difference_type;
    _Distance_type size = _last - _first;
    int t = 1;
    while(t < size - 1)
    {
        int s = t;
        t = 2 * s;
        int i = 0;
        while(i + t <= size - 1)
        {
            _mergeSortedLists(_first + i, _first + i + s - 1, _first + i + t - 1, _comp);
            i = i + t;
        }
        if (i + s < size)
            _mergeSortedLists(_first + i, _first + i + s - 1, _first + size - 1, _comp);
    }
}

template <typename _RandomAccessIterator, typename _Compare>
void mergeSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    if((_last - _first) > 1)
    {
        auto mid = (_last - _first + 1) / 2 + _first - 1;
        mergeSort(_first, mid + 1, _comp);
        mergeSort(mid + 1, _last, _comp);
        _mergeSortedLists(_first, mid, _last - 1, _comp);
    }
}
// 6.Quick Sort
// Time complexity: O(nlogn)
// Space complexity: O(logn)
// unstable sort
// in-place sort
template <typename _RandomAccessIterator, typename _Compare>
_RandomAccessIterator _split(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    auto i = _first;
    auto x = *_first;
    for(auto j = _first + 1; j != _last; ++j) {
        if (!_comp(*j, x))
            continue;
        else {
            i++;
            if (i != j)
                std::swap(*i, *j);
        }
    }
    std::swap(*_first, *i);
    return i;
}

template <typename _RandomAccessIterator, typename _Compare>
void quickSort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
{
    if(_first != _last)
    {
        auto w = _split(_first, _last, _comp);
        quickSort(_first, w, _comp);
        quickSort(w + 1, _last, _comp);
    }
}

// 7.Heap Sort
// Time complexity: O(nlogn)
// Space complexity: O(1)
// unstable sort
// in-place sort
// #include "heap/heap.h"
#endif //SORT_H
