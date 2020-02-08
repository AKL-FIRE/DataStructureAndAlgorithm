//
// Created by lcy19 on 2020/1/31.
//

#ifndef ADJACENCYWDIGRAPH_H
#define ADJACENCYWDIGRAPH_H

#include "graph.h"

// Weighted Directed Graph By Adjacency Matrix

template <typename T>
class adjacencyWDigraph : public graph<T> {
protected:
    int n; // number of vertices
    int e; // number of edge
    T **a; // data stored the graph
    T noEdge; // notation of the no exist edge

public:
    adjacencyWDigraph(int numOfVertices = 0, T theNoEdge = 0)
    {
        if(numOfVertices < 0)
            throw illegalParameterValue("number of vertices must be >= 0");
        n = numOfVertices;
        e = 0;
        noEdge = theNoEdge;
        make2dArray(a, n + 1, n + 1);
        for(int i = 1; i <= n; i++)
            std::fill(a[i], a[i] + n + 1, noEdge); // Assigns the given value to the elements in the range [first, last).
    }
    ~adjacencyWDigraph() override {delete2dArray(a, n + 1);}
    int numberOfVertices() const override {return n;}
    int numberOfEdges() const override {return e;}
    bool directed() const override {return true;}
    bool weighted() const override {return true;}
    bool existsEdge(int, int) const override;
    void insertEdge(edge<T>*) override;
    void eraseEdge(int, int) override;
    void checkVertex(int) const;
    int degree(int theVertex) const override {};
    int outDegree(int) const override;
    int inDegree(int) const override;
    void printData() const;
    void dfs(int);
    void searchAllPath(int, int);
    void minMaxCapacity(int, int);

    class myIterator : public vertexIterator<T>
    {
    public:
        myIterator(T* theRow, T theNoEdge, int numberOfVertices) : row(theRow), noEdge(theNoEdge), n(numberOfVertices)
        {
            currentVertex = 1;
        }
        ~myIterator() = default;

        int next(T& theWeight)
        {
            for(int j = currentVertex; j <= n; j++)
                if(row[j] != noEdge)
                {
                    currentVertex = j + 1;
                    theWeight = row[j];
                    return j;
                }
            currentVertex = n + 1;
            return 0;
        }

        int next()
        {
            for(int j = currentVertex; j <= n; j++)
                if(row[j] != noEdge)
                {
                    currentVertex = j + 1;
                    return j;
                }
            currentVertex = n + 1;
            return 0;
        }

    protected:
        T* row;
        T noEdge;
        int n;
        int currentVertex;
    };

    std::shared_ptr<vertexIterator<T>> iterator(int theVertex)
    {
        checkVertex(theVertex);
        // return new myIterator(a[theVertex], noEdge, n);
        return std::make_shared<myIterator>(a[theVertex], noEdge, n);
    }

private:
    void rDfs(int, std::vector<bool>&);
    // void searchDfs(int, int, std::vector<bool>&, std::vector<int>&);
    void searchDfs(int, int, std::vector<bool>&, std::vector<int>&, int&, std::vector<int>&);
};

template <typename T>
bool adjacencyWDigraph<T>::existsEdge(int i, int j) const
{
    return !(i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge);
}

template <typename T>
void adjacencyWDigraph<T>::insertEdge(edge<T> *theEdge)
{
    int v1 = theEdge->get_vertex1();
    int v2 = theEdge->get_vertex2();
    if(v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
    {
        std::strstream s;
        s << "(" << v1 << ", " << v2 << ") is not a permissible edge";
        throw illegalParameterValue(s);
    }
    if(a[v1][v2] == noEdge)
        e++;
    a[v1][v2] = theEdge->get_weight();
}

template <typename T>
void adjacencyWDigraph<T>::eraseEdge(int i, int j)
{
    if(i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
    {
        a[i][j] = noEdge;
        e--;
    }
}

template <typename T>
void adjacencyWDigraph<T>::checkVertex(int theVertex) const
{
    if(theVertex < 1 || theVertex > n)
    {
        std::strstream s;
        s << "no vertex " << theVertex;
        throw illegalParameterValue(s);
    }
}

template <typename T>
int adjacencyWDigraph<T>::outDegree(int theVertex) const
{
    checkVertex(theVertex);

    int sum = 0;
    for(int j = 1; j <= n; j++)
        if(a[theVertex][j] != noEdge)
            sum++;

     return sum;
}

template <typename T>
int adjacencyWDigraph<T>::inDegree(int theVertex) const
{
    checkVertex(theVertex);

    int sum = 0;
    for(int j = 0; j <= n; j++)
        if(a[j][theVertex] != noEdge)
            sum++;

    return sum;
}

template <typename T>
void adjacencyWDigraph<T>::printData() const
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void adjacencyWDigraph<T>::dfs(int v)
{
    std::vector<bool> label(n, false); // is_reached
    rDfs(v, label);
}

template <typename T>
void adjacencyWDigraph<T>::rDfs(int v, std::vector<bool> &label)
{
    label[v - 1] = true;

    std::cout << v << "->";

    auto iv = iterator(v);
    int u;
    while((u = iv->next()) != 0)
        if(label[u - 1] == false)
            rDfs(u, label);
}
/*
template <typename T>
void adjacencyWDigraph<T>::searchAllPath(int start, int end)
{
    std::vector<bool> label(n, false);
    std::vector<int> path;
    searchDfs(start, end, label, path);
}
*/
/*
template <typename T>
void adjacencyWDigraph<T>::searchDfs(int start, int end, std::vector<bool> &label, std::vector<int> &path)
{
    label[start - 1] = true;
    path.push_back(start);

    if(start == end)
    {
        // 此时已找到一条路径
        for(int i = 0; i < path.size(); i++)
            std::cout << path[i] << "->";
        std::cout << std::endl;
        path.erase(path.end() - 1);
        label[start - 1] = false;
        return;
    }

    auto iv = iterator(start);
    int u;
    while((u = iv->next()) != 0)
        if(label[u - 1] == false)
            searchDfs(u, end, label, path);
    if(u == 0)
    {
        path.erase(path.end() - 1);
        label[start - 1] = false;
    }
}
 */

template <typename T>
void adjacencyWDigraph<T>::searchAllPath(int start, int end)
{
    std::vector<bool> label(n, false);
    std::vector<int> path;
    std::vector<int> result;
    int minmax_path = 0;
    searchDfs(start, end, label, path, minmax_path, result);
    std::cout << "The final result: \n";
    for(const auto &c : result)
        std::cout << c << "->";
}

template <typename T>
void adjacencyWDigraph<T>::searchDfs(int start, int end, std::vector<bool> &label, std::vector<int> &path, int& minmax_path, std::vector<int> &result)
{
    label[start - 1] = true;
    path.push_back(start);


    if(start == end)
    {
        // 此时已找到一条路径
        for(int i = 0; i < path.size(); i++)
            std::cout << path[i] << "->";
        std::cout << std::endl;

        // 更新minmax_path
        int min = a[path[0]][path[1]];
        for(int i = 1; i < path.size() - 1; i++)
        {
            if(a[path[i]][path[i + 1]] < min)
                min = a[path[i]][path[i + 1]];
        }

        if(min > minmax_path)
        {
            minmax_path = min;
            // 将当前路径copy到result中
            if(result.empty())
                // std::copy(path.begin(), path.end(), result.begin());
            {
                for(const auto &c : path)
                    result.push_back(c);
            }
            else
            {
                result.clear();
                // std::copy(path.begin(), path.end(), result.begin());
                for(const auto &c : path)
                    result.push_back(c);
            }

        }

        path.erase(path.end() - 1);
        label[start - 1] = false;
        return;
    }

    auto iv = iterator(start);
    int u;
    while((u = iv->next()) != 0)
        if(label[u - 1] == false)
            searchDfs(u, end, label, path, minmax_path, result);
    if(u == 0)
    {
        path.erase(path.end() - 1);
        label[start - 1] = false;
    }
}

template <typename T>
void adjacencyWDigraph<T>::minMaxCapacity(int start, int end)
{
    std::vector<int> width(n + 1, -1000);
    std::vector<int> previous(n + 1, -1);

    width[start] = 1000;
    std::vector<std::pair<int, int>> Q;
    for(int i = 1; i <= n; i++)
        Q.emplace_back(i, width[i]);
    std::make_heap(Q.begin(), Q.end(), [](const auto &e1, const auto &e2){return e1.second < e2.second;});

    while(!Q.empty())
    {
        int u = Q[0].first;
        std::pop_heap(Q.begin(), Q.end());
        Q.pop_back();
        // if(width[u] == -1000 || u == end)
        if(u == end)
            break;

        auto iv = iterator(u);
        int v;
        while((v = iv->next()) != 0)
        {
            int alt = std::max(width[v], std::min(width[u], a[u][v]));
            if(alt > width[v])
            {
                width[v] = alt;
                // Q[v - 1].second = width[v];
                auto temp = std::find_if(Q.begin(), Q.end(), [v](const auto &e1){return e1.first == v;});
                temp->second = width[v];
                previous[v] = u;
                std::make_heap(Q.begin(), Q.end(), [](const auto &e1, const auto &e2){return e1.second < e2.second;});
            }
        }
    }
    // output the final path result
    int current = end;
    while(current != start)
    {
        std::cout << current << "<-";
        current = previous[current];
    }
    std::cout << start;
}

#endif //ADJACENCYWDIGRAPH_H
