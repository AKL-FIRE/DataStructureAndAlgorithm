//
// Created by lcy19 on 2020/2/3.
//

#ifndef HEAP_H
#define HEAP_H

#include <iterator>
#include "../Tool/utlity.h"

// To create a Min Heap, So the compare must means "<"
namespace mine
{
    template <typename _RandomAccessIterator, typename _Compare, typename _DistanceType>
    inline void sift_down(_RandomAccessIterator _first,  _DistanceType position, _DistanceType _len, _Compare _comp)
    {
        // assume when _comp mean ">" (a - b > 0)
        bool done = false;
        // int position = i - _first + 1;
        _RandomAccessIterator i = _first + (position - 1);
        if(2 * position > _len)
            return;
        while(2 * position <= _len && !done)
        {

            i += position;
            position *= 2;
            if(position + 1 <= _len && _comp(*(i + 1),  *i)) // *(i + 1) > *(i)
            {
                i++;
                position++;

                if(!_comp(*(i - position / 2 - 1), *i)) // *(i - position / 2) father > *(i) son
                    std::swap(*(i - position / 2 - 1), *i);
                else
                    done = true;
            } else
            {
                if(!_comp(*(i - position / 2), *i)) // *(i - position / 2) father > *(i) son
                    std::swap(*(i - position / 2), *i);
                else
                    done = true;
            }
        }
    }

    template <typename _RandomAccessIterator, typename _Compare, typename _DistanceType>
    inline void sift_up(_RandomAccessIterator _first,  _DistanceType position, _Compare _comp)
    {
        // assume when _comp mean ">" (a - b > 0)
        bool done = false;
        // int position = i - _first + 1;
        _RandomAccessIterator i = _first + (position - 1);
        if(position == 1)
            return;
        while(position != 1 && !done)
        {
            if(position % 2 == 0)
            {
                if(_comp(*i, *(i - position / 2))) // *i < *(i - position / 2)
                    std::swap(*i, *(i - position / 2));
                else
                    done = true;
                i -= position / 2;
                position /= 2;
            } else
            {
                if(_comp(*i, *(i - position / 2 - 1)))
                    std::swap(*i, *(i - position / 2 - 1));
                else
                    done = true;
                i -= position / 2 + 1;
                position /= 2;
            }
        }
    }

    // This function just adjust the heap structure, you need to add the element to the back of the list first.
    template <typename _RandomAccessIterator, typename _Compare>
    inline void insert_heap(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
    {
        _first++;
        if(_last - _first < 1)
            return;
        mine::sift_up(_first, _last - _first, _comp);
    }

    // swap the first element and the last element, you need to delete the last element.
    template <typename _RandomAccessIterator, typename _Compare>
    inline void pop_heap(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
    {
        if(_last - _first <= 1)
            return;
        _first++;
        _RandomAccessIterator i = _first;
        std::swap(*i, *(_last - 1));
        _last--;
        mine::sift_down(_first, (_first + 1) - _first, _last - _first, _comp);
    }

    template <typename _RandomAccessIterator, typename _Compare>
    inline void heap_sort(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
    {
        if(_last - _first < 2)
            return;
        for(auto i = 1; i <= (_last - _first); i++)
            mine::pop_heap(_first, _last - (i - 1), _comp);
    }

    template <typename _RandomAccessIterator, typename _Compare, typename _ValueType>
    inline void decrease_key(_RandomAccessIterator _first, _RandomAccessIterator _last, _RandomAccessIterator pos, _ValueType val, _Compare _comp)
    {
        _first++;
        if(pos - _first >= 0 && _last - pos > 0)
        {
            if(_comp(val, *pos)) {
                *pos = val;
                mine::sift_up(_first, pos - _first + 1, _comp);
            }
            else {
                *pos = val;
                mine::sift_down(_first, pos - _first + 1, _last - _first, _comp);
            }
        }
    }

// array[1...n]
    template <typename _RandomAccessIterator, typename _Compare>
    inline void make_heap(_RandomAccessIterator _first, _RandomAccessIterator _last, _Compare _comp)
    {
        typedef typename std::iterator_traits<_RandomAccessIterator>::value_type _ValueType; // get the value type
        typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type _DistanceType; // get the distance type

        // typedef decltype(_comp) _Cmp;
        // __gnu_cxx::__ops::_Iter_comp_iter<_Cmp> __cmp(_GLIBCXX_MOVE(_comp));

        if(_last - _first < 2)
            return;

        _first++; // adjust the first point

        const _DistanceType _len = _last - _first;
        _DistanceType _position = _len / 2;
        for(auto i = _position; i >= 1; i--)
        {
            mine::sift_down(_first, i, _len, _comp);
        }
    }
};


#endif //HEAP_H
