//
// Created by lcy19 on 2020/2/7.
//

#ifndef LINKEDWDIGRAPH_H
#define LINKEDWDIGRAPH_H

#include "../LinearList/chain.hpp"
#include "graph.h"
#include "../heap/heap.h"

// Directed Weighted Graph By Linked List

template <typename T>
struct weightedNode
{
    int vertex; // x -> vertex
    T weight; // the weight of edge(x, vertex)
    weightedNode(int theVertex = 0, const T& theWeight = T()) : vertex(theVertex), weight(theWeight) {}
    ~weightedNode() = default;
    bool operator==(const weightedNode<T>& e) {return vertex == e.vertex;}
    bool operator!=(const weightedNode<T>& e) {return vertex != e.vertex;}
};

template <typename T>
std::ostream& operator<<(std::ostream &out, const weightedNode<T> &x)
{
    out << x.vertex;
    return out;
}

template <typename T>
class graphWChain : public chain<T>
{
public:
    explicit graphWChain(int initialCapacity = 10) : chain<T>(initialCapacity) {}
    ~graphWChain() override = default;
    chainNode<T>* eraseElement(int j)
    {
        auto currentNode = chain<T>::firstNode;
        auto deleteNode = currentNode;
        if(currentNode->element.vertex == j)
        {
            chain<T>::firstNode = currentNode->next;
            chain<T>::listSize--;
            return deleteNode;
        } else
        {
            while(currentNode->next->element.vertex != j && currentNode->next != nullptr)
                currentNode = currentNode->next;

            if(currentNode->next->element.vertex == j) // find the element
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

template <typename T>
class linkedWDigraph : public graph<T>
{
protected:
    int n; // number of vertices
    int e; // number of edges
    graphWChain<weightedNode<T>> *aList; // linked lists to store edges

public:
    explicit linkedWDigraph(int numberOfVertices = 0);
    ~linkedWDigraph() override;
    int numberOfVertices() const override;
    int numberOfEdges() const override;
    bool existsEdge(int i, int j) const override;
    void insertEdge(edge<T>* theEdge) override;
    void eraseEdge(int i, int j) override;
    int degree(int) const override;
    int inDegree(int) const override;
    int outDegree(int) const override;
    bool directed() const override {return true;}
    bool weighted() const override {return true;}

    // Famous algorithm in graph

    // 1.Dijkstra algorithm using min-heap to improve
    std::vector<T> dijkstraAlgorithm(int theVertex, T infinity);

    class myIterator : public vertexIterator<T>
    {
    public:
        explicit myIterator( graphWChain<weightedNode<T>>* theVertex) : currentVertex(theVertex), currentNode(theVertex->begin())
        {
            currentSize = 1;
        }
        ~myIterator() override = default;
        int next() override
        {
            if(currentSize <= currentVertex->size())
            {
                currentSize++;
                return (*(currentNode++)).vertex;
            } else
                return -1;
        }
        int next(T& theWeight) override
        {
            if(currentSize <= currentVertex->size())
            {
                currentSize++;
                theWeight = (*currentNode).weight;
                return (*(currentNode++)).vertex;
            } else
            {
                theWeight = T();
                return -1;
            }
        }
    protected:
        graphWChain<weightedNode<T>>* currentVertex;
        typename chain<weightedNode<T>>::iterator currentNode;
        int currentSize;
    };

    std::shared_ptr<vertexIterator<T>> iterator(int theVertex) override
    {
        // return new myIterator(a[theVertex], noEdge, n);
        return std::make_shared<myIterator>(&aList[theVertex]);
    }
};

template<typename T>
linkedWDigraph<T>::linkedWDigraph(int numberOfVertices) {
    if(numberOfVertices < 0)
        throw illegalParameterValue("number of vertices must be > 0");
    n = numberOfVertices;
    e = 0;
    aList = new graphWChain<weightedNode<T>>[n + 1];
}

template<typename T>
linkedWDigraph<T>::~linkedWDigraph() {
    delete [] aList;
}

template<typename T>
int linkedWDigraph<T>::numberOfVertices() const {
    return n;
}

template<typename T>
int linkedWDigraph<T>::numberOfEdges() const {
    return e;
}

template<typename T>
bool linkedWDigraph<T>::existsEdge(int i, int j) const {
    weightedNode<T> temp(j, T());
    if(i < 1 || j < 1 || i > n || j > n || aList[i].indexOf(temp, [](const auto& e1, const auto& e2)->bool{return e1.vertex == e2.vertex;}) == -1)
        return false;
    else
        return true;
}

template<typename T>
void linkedWDigraph<T>::insertEdge(edge<T> *theEdge) {
    aList[theEdge->get_vertex1()].insert(0, weightedNode<T>(theEdge->get_vertex2(), theEdge->get_weight()));
    e++;
}

template<typename T>
void linkedWDigraph<T>::eraseEdge(int i, int j) {
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

template<typename T>
int linkedWDigraph<T>::degree(int theVertex) const {
    throw illegalParameterValue("degree undefined.");
}

template<typename T>
int linkedWDigraph<T>::inDegree(int theVertex) const {
    int sum = 0;
    for(int j = 1; j <= n; j++) {
        weightedNode<T> temp(theVertex, T());
        if (aList[j].indexOf(temp, [](const auto &e1, const auto &e2) -> bool { return e1.vertex == e2.vertex; }) != -1)
            sum++;
    }
    return sum;
}

template<typename T>
int linkedWDigraph<T>::outDegree(int theVertex) const {
    return aList[theVertex].size();
}

template<typename T>
std::vector<T> linkedWDigraph<T>::dijkstraAlgorithm(int theVertex, T infinity) {
    std::vector<T> distance(n + 1); // store the left vertex and its distance
    // std::vector<int> Y; // store the left vertex

    distance[theVertex] = 0;
    std::vector<std::pair<int, T>> H;
    H.push_back(std::pair<int, T>(0, infinity));
    for(int i = 1; i <= n; i++)
    {
        if(i == theVertex)
            continue;
        // Y.push_back(i);
        weightedNode<T> temp(i, T());
        int y;
        if((y = aList[theVertex].indexOf(temp, [](const auto &e1, const auto &e2) -> bool { return e1.vertex == e2.vertex; })) != -1)
        {
            distance[i] = aList[theVertex].get(y).weight;
            H.push_back(std::pair<int, T>(i, distance[i]));
        } else
        {
            distance[i] = infinity;
            H.push_back(std::pair<int, T>(i, distance[i]));
        }
    }
    auto comp =  [](const auto& e1, const auto& e2){return e1.second < e2.second;};
    mine::make_heap(H.begin(), H.end(), comp);
    for(int j = 1; j <= n - 1; j++)
    {
        int y = H[1].first;
        mine::pop_heap(H.begin(), H.end(), comp);
        H.pop_back();

        auto it = iterator(y);
        int v;
        T lengthY_V;
        while((v = it->next(lengthY_V)) != -1)
        {
            // int index = aList[y].indexOf(weightedNode<T>(v, T()), [](const auto &e1, const auto &e2) -> bool { return e1.vertex == e2.vertex; });
            // T lengthY_V = aList[y].get(index).weight;
            if(distance[y] + lengthY_V < distance[v])
            {
                distance[v] = lengthY_V + distance[y];
                auto v_pos = std::find_if(H.begin(), H.end(), [v](const auto& e1){return e1.first == v;});
                mine::decrease_key(H.begin(), H.end(), v_pos, std::pair<int, T>(v, distance[v]), comp);
            }
        }
    }
    return distance;
}


#endif //LINKEDWDIGRAPH_H
