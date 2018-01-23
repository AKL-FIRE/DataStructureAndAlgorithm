//
//  arrayList.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 23/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef arrayList_hpp
#define arrayList_hpp

#include "linearList.hpp"

template <typename T>
class arrayList : public linearList<T>
{
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() {delete [] element;}
    
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream &out) const;
    
    int capacity() const {return arrayLength;}
    
    class iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        
        iterator(pointer thePosition = 0) {position = thePosition;}
        
        reference operator*() const {return *position;}
        pointer operator->() const {return &*position;}
        
        iterator& operator++() {++position; return *this;} //++position
        iterator operator++(int) {iterator old = *this; ++position; return old;}  //position++
        iterator& operator--() {--position; return *this;}
        iterator operator--(int) {iterator old = *this; --position; return old;}
        
        bool operator!=(const iterator right) const {return position != right.position;}
        bool operator==(const iterator right) const {return position == right.position;}
    protected:
        pointer position;
    };
    
    iterator begin() {return iterator(element);}
    iterator end() {return iterator(element + listSize);}
    
    const T& get(const iterator &it) const;
    void erase(iterator &it);
    void insert(iterator &it, const T& theElement);
    
protected:
    void checkIndex(int theIndex) const;
    T* element;
    int arrayLength;
    int listSize;
};

template <typename T>
arrayList<T>::arrayList(int initialCapacity)
{
    if(initialCapacity < 1)
    {
        std::strstream s;
        s << "Initial capacity = " << initialCapacity << " must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    make1dArray(element, arrayLength);
    listSize = 0;
}

template <typename T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    make1dArray(element, arrayLength);
    std::copy(theList.element, theList.element + listSize, element);
}

template <typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if(theIndex < 0 || theIndex >= listSize)
    {
        std::strstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }
}

template <typename T>
T& arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template <typename T>
const T& arrayList<T>::get(const iterator &it) const
{
    return *it;
}

template <typename T>
int arrayList<T>::indexOf(const T &theElement) const
{
    int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
    if(theIndex == listSize)
        return -1;
    else
        return theIndex;
}

template <typename T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);
    listSize--;
}

template <typename T>
void arrayList<T>::erase(iterator &it)
{
    iterator temp = it;
    std::copy(++temp, ++(this->end()), it);
    listSize--;
}

template <typename T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex < 0 || theIndex > listSize)
    {
        std::strstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str());
    }
    if(listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}

template <typename T>
void arrayList<T>::insert(iterator &it, const T &theElement)
{
    if(listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }
    std::copy_backward(it, ++(this->end()), ++(++(this->end())));
    *it = theElement;
    listSize++;
}

template <typename T>
void arrayList<T>::output(std::ostream &out) const
{
    std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout," "));
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const arrayList<T> &x)
{
    x.output(out);
    return out;
}

#endif /* arrayList_hpp */
