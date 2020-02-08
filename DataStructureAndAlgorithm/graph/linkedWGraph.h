//
// Created by lcy19 on 2020/2/7.
//

#ifndef LINKEDWGRAPH_H
#define LINKEDWGRAPH_H

#include "linkedWDigraph.h"
#include "../heap/heap.h"
#include "../Tool/union_find.h"

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

    // Algorithms: 1.KRUSKAL 2.Prim
    std::vector<edge<T>> kruskal();
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

template<typename T>
std::vector<edge<T>> linkedWGraph<T>::kruskal() {
    std::vector<edge<T>> result;
    std::vector<edge<T>> edges;
    edges.push_back(edge<T>(-1, -1, T())); // placeholder
    std::vector<bool> label(linkedWDigraph<T>::n + 1, false);

    for(int i = 1; i <= linkedWDigraph<T>::n; i++)
    {
        auto it = linkedWDigraph<T>::iterator(i);
        int v;
        T weight;
        while((v = it->next(weight)) != -1)
        {
            edges.push_back(edge<T>(i, v, weight));
        }
    }
    // sort the edges
    mine::heap_sort(edges.begin(), edges.end(), [](const auto& e1, const auto&e2){return e1.get_weight() < e2.get_weight();});
    // create set
    unionFind uf(linkedWDigraph<T>::e);
    while(result.size() < linkedWDigraph<T>::n - 1)
    {
        edge<T> temp = edges.back();
        edges.pop_back();
        if(!uf.isInSameSet(temp.get_vertex1(), temp.get_vertex2()))
        {
            result.push_back(temp);
            uf.unite(uf.find(temp.get_vertex1()), uf.find(temp.get_vertex2()));
        }
    }
    return result;
}


#endif //LINKEDWGRAPH_H
