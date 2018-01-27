//
//  extendedChain.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 24/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef extendedChain_hpp
#define extendedChain_hpp

#include "extendeLinearList.hpp"
#include "chain.hpp"

template <typename T>
class extendedChain : public extendedLinearList<T>, public chain<T>
{
public:
    extendedChain(int initialCapacity = 10) : chain<T>(initialCapacity) {lastNode = nullptr;}
    extendedChain( extendedChain<T> &x) : chain<T>(x)
    {
        chainNode<T> *p = chain<T>::firstNode;
        for(int i = 0; i < chain<T>::listSize - 1; i++)
            p = p->next;
        lastNode = p;
    }
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    virtual void clear();
    virtual void push_back(const T &theElement);

protected:
    chainNode<T> *lastNode;
};

template <typename T>
void extendedChain<T>::insert(int theIndex,  const T &theElement)
{
    if(theIndex < 0 || theIndex > chain<T>::listSize)
    {
        std::strstream s;
        s << "index = " << theIndex << " size = " << chain<T>::listSize;
        throw illegalParameterValue(s.str());
    }
    
    if(theIndex == 0)
    {
        chain<T>::firstNode = new chainNode<T>(theElement, chain<T>::firstNode);
        lastNode = chain<T>::firstNode;
    }
    else
    {
        if(theIndex != chain<T>::listSize)
        {
            chainNode<T> *p = chain<T>::firstNode;
            for(int i = 0; i < theIndex - 1; i++)
                p = p->next;
            p->next = new chainNode<T>(theElement, p->next);
        }else
        {
            chainNode<T> *p = chain<T>::firstNode;
            for(int i = 0; i < theIndex - 1; i++)
                p = p->next;
            p->next = new chainNode<T>(theElement, p->next);
            lastNode = p->next;
        }
    }
    chain<T>::listSize++;
}

template <typename T>
void extendedChain<T>::erase(int theIndex)
{
    chain<T>::checkIndex(theIndex);
    
    chainNode<T> *deleteNode;
    if(theIndex == 0)
    {
        deleteNode = chain<T>::firstNode;
        chain<T>::firstNode = chain<T>::firstNode->next;
    }else
    {
        if(theIndex != chain<T>::listSize - 1)
        {
            chainNode<T> *p = chain<T>::firstNode;
            for(int i = 0; i < theIndex - 1; i++)
                p = p->next;
        
            deleteNode = p->next;
            p->next = p->next->next;
        }else
        {
            chainNode<T> *p = chain<T>::firstNode;
            for(int i = 0; i < theIndex - 1; i++)
                p = p->next;
            
            deleteNode = p->next;
            p->next = p->next->next;
            lastNode = p;
        }
    }
    chain<T>::listSize--;
    delete deleteNode;
}

template <typename T>
void extendedChain<T>::clear()
{
    while(chain<T>::firstNode != nullptr)
    {
        chainNode<T> *nextNode = chain<T>::firstNode->next;
        delete chain<T>::firstNode;
        chain<T>::firstNode = nextNode;
    }
    chain<T>::listSize = 0;
}

template <typename T>
void extendedChain<T>::push_back(const T &theElement)
{
    chainNode<T> *newNode = new chainNode<T>(theElement, nullptr);
    if(chain<T>::firstNode == nullptr)
        chain<T>::firstNode = lastNode = newNode;
    else
    {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    chain<T>::listSize++;
}
#endif /* extendedChain_hpp */
