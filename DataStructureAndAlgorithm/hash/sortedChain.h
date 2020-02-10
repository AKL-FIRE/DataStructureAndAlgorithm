//
// Created by lcy19 on 2020/2/9.
//

#ifndef SORTEDCHAIN_H
#define SORTEDCHAIN_H

#include "dictionary.h"

template <typename K, typename E>
struct pairNode
{
    std::pair<const K, E> element;
    pairNode<K, E>* next;

    pairNode() = default;
    pairNode(const std::pair<const K, E> &element) {this->element = element;}
    pairNode(const std::pair<const K, E> &element, pairNode<K, E> *next) {this->element = element; this->next = next;}
};

template<typename K, typename E>
class sortedChain : public dictionary<K, E>
{
public:
    sortedChain() : dSize(0), firstNode(nullptr) {}
    ~sortedChain() override;
    bool empty() const override {return dSize == 0;}
    int size() const override {return dSize;}
    std::pair<const K, E>* find(const K&) const override;
    void erase(const K&) override;
    void insert(const std::pair<const K, E>&) override;

protected:
    int dSize;
    pairNode<K, E>* firstNode;
};

template<typename K, typename E>
sortedChain<K, E>::~sortedChain() {
    auto p = firstNode;
    auto tp = p;
    while(p != nullptr)
    {
        tp = p;
        p = p->next;
        delete tp;
    }
}

template<typename K, typename E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const {
    auto currentNode = firstNode;
    while(currentNode != nullptr && currentNode->element.first != theKey)
        currentNode = currentNode->next;
    if(currentNode != nullptr && currentNode->element.first == theKey)
        return &currentNode->element;
    return nullptr;
}

template<typename K, typename E>
void sortedChain<K, E>::erase(const K& theKey) {
    auto p = firstNode;
    pairNode<K, E>* tp = nullptr;

    while(p != nullptr && p->element.first < theKey)
    {
        tp = p;
        p = p->next;
    }

    if(p != nullptr && p->element.first == theKey)
    {
        if(tp == nullptr) // delete the first node
            firstNode = p->next;
        else // delete other node
            tp->next = p->next;

        delete p;
        dSize--;
    }
}

template<typename K, typename E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& thePair) {
    auto p = firstNode;
    pairNode<K, E>* tp = nullptr;

    // search the right place to insert
    while(p != nullptr && p->element.first < thePair.first)
    {
        tp = p;
        p = p->next;
    }

    // if thePair is already in dictionary, update it
    if(p != nullptr && p->element.first == thePair.first)
    {
        p->element.second = thePair.second;
        return;
    }

    auto newNode = new pairNode<K, E>(thePair, p);

    // insert the first node, or adjust previous node's pointer
    if(tp == nullptr)
        firstNode = newNode;
    else
        tp->next = newNode;

    dSize++;
}



#endif //SORTEDCHAIN_H
