//
// Created by lcy19 on 2020/2/7.
//

#ifndef LINKEDWGRAPH_H
#define LINKEDWGRAPH_H

#include "linkedWDigraph.h"

// Undirected Weighted Graph By Linked List Derived from linkedWDigraph

template <typename T>
class linkedWGraph : public linkedWDigraph<T>
{
public:
    explicit linkedWGraph(int numberOfVertices = 0);
    void insertEdge(edge<T>* theEdge) override;
    void eraseEdge(int i, int j) override;
    int degree(int) const override;
    int inDegree(int) const override;
    int outDegree(int) const override;
    bool directed() const override {return true;}
};

template<typename T>
linkedWGraph<T>::linkedWGraph(int numberOfVertices) : linkedWDigraph<T>(numberOfVertices) {}

template<typename T>
void linkedWGraph<T>::insertEdge(edge<T> *theEdge) {
    linkedWDigraph<T>::aList[theEdge->get_vertex1()].insert(0, weightedNode<T>(theEdge->get_vertex2(), theEdge->get_weight()));
    linkedWDigraph<T>::e++;
    linkedWDigraph<T>::aList[theEdge->get_vertex2()].insert(0, weightedNode<T>(theEdge->get_vertex1(), theEdge->get_weight()));
}

template<typename T>
void linkedWGraph<T>::eraseEdge(int i, int j) {
    linkedWDigraph<T>::eraseEdge(i, j);
    linkedWDigraph<T>::eraseEdge(j, i);
    linkedWDigraph<T>::e++;
}

template<typename T>
int linkedWGraph<T>::degree(int theVertex) const {
    return (linkedWDigraph<T>::inDegree(theVertex) + linkedWDigraph<T>::outDegree(theVertex)) / 2;
}

template<typename T>
int linkedWGraph<T>::inDegree(int) const {
    throw illegalParameterValue("In degree is not defined.");
}

template<typename T>
int linkedWGraph<T>::outDegree(int) const {
    throw illegalParameterValue("Out degree is not defined.");
}


#endif //LINKEDWGRAPH_H
