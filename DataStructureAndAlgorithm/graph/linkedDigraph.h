//
// Created by lcy19 on 2020/2/7.
//

#ifndef LINKEDDIGRAPH_H
#define LINKEDDIGRAPH_H

#include "../LinearList/chain.hpp"
#include "graph.h"
// Directed Unweighted Graph By Linked List

template<typename T>
class graphChain : public chain<T>
{
public:
    explicit graphChain(int initialCapacity = 10) : chain<T>(initialCapacity) {}
    ~graphChain() override = default;
    chainNode<T>* eraseElement(int j)
    {
        auto currentNode = chain<T>::firstNode;
        auto deleteNode = currentNode;
        if(currentNode->element == j)
        {
            chain<T>::firstNode = currentNode->next;
            chain<T>::listSize--;
            return deleteNode;
        } else
        {
            while(currentNode->next->element != j && currentNode->next != nullptr)
                currentNode = currentNode->next;

            if(currentNode->next->element == j) // find the element
            {
                deleteNode = currentNode->next;
                currentNode->next = currentNode->next->next;
                chain<T>::listSize--;
                return deleteNode;
            } else
            {
                return nullptr;
            }
        }
    }
};

class linkedDigraph : public graph<bool>
{
protected:
    int n; // number of vertices
    int e; // number of edges
    graphChain<int> *aList; // linked lists to store edges

public:
    explicit linkedDigraph(int numberOfVertices = 0);
    ~linkedDigraph() override;
    int numberOfVertices() const override;
    int numberOfEdges() const override;
    bool existsEdge(int i, int j) const override;
    void insertEdge(edge<bool>* theEdge) override;
    void eraseEdge(int i, int j) override;
    int degree(int) const override;
    int inDegree(int) const override;
    int outDegree(int) const override;
    bool directed() const override {return true;}
    bool weighted() const override {return false;}

    class myIterator : public vertexIterator<bool>
    {
    public:
        explicit myIterator( graphChain<int>* theVertex) : currentVertex(theVertex), currentNode(theVertex->begin())
        {
            currentSize = 1;
        }
        ~myIterator() override = default;
        int next() override
        {
            if(currentSize < currentVertex->size())
            {
                currentSize++;
                return *(currentNode++);
            } else
                return -1;
        }
        int next(bool& theWeight) override
        {
            if(currentSize < currentVertex->size())
            {
                currentSize++;
                theWeight = true;
                return *(currentNode++);
            } else
            {
                theWeight = false;
                return -1;
            }
        }
    protected:
        graphChain<int>* currentVertex;
        chain<int>::iterator currentNode;
        int currentSize;
    };

   std::shared_ptr<vertexIterator<bool>> iterator(int theVertex) override
   {
       // return new myIterator(a[theVertex], noEdge, n);
        return std::make_shared<myIterator>(&aList[theVertex]);
   }
};

linkedDigraph::linkedDigraph(int numberOfVertices)
{
    if(numberOfVertices < 0)
        throw illegalParameterValue("number of vertices must be > 0");
    n = numberOfVertices;
    e = 0;
    aList = new graphChain<int>[n + 1];
}

linkedDigraph::~linkedDigraph() {
    delete [] aList;
}

int linkedDigraph::numberOfVertices() const {
    return n;
}

int linkedDigraph::numberOfEdges() const {
    return e;
}

bool linkedDigraph::existsEdge(int i, int j) const {
    return !(i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(j) == -1);
}

void linkedDigraph::insertEdge(edge<bool> *theEdge) {
    if(aList[theEdge->get_vertex1()].indexOf(theEdge->get_vertex2()) == -1)
    {
        aList[theEdge->get_vertex1()].insert(0, theEdge->get_vertex2());
        e++;
    }
}

void linkedDigraph::eraseEdge(int i, int j) {
    if(i >= 1 && j >= 1 && i <= n && j <= n)
    {
        auto v = aList[i].eraseElement(j);
        if(v != nullptr)
        {
            e--;
            delete v;
        }
    }
}

int linkedDigraph::degree(int theVertex) const {
    throw illegalParameterValue("degree undefined.");
}

int linkedDigraph::inDegree(int theVertex) const {
    int sum = 0;
    for(int j = 1; j <= n; j++)
        if(aList[j].indexOf(theVertex) != -1)
            sum++;
    return sum;
}

int linkedDigraph::outDegree(int theVertex) const {
    return aList[theVertex].size();
}

#endif //LINKEDDIGRAPH_H
