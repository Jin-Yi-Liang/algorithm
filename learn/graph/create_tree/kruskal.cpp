#include <bits/stdc++.h>
using namespace std;

int find(int i, vector<int> &parent)
{
    if (parent[i] != i)
    {
        return parent[i] = find(parent[i], parent);
    }
    return parent[i];
}

void my_union(int i, int j, vector<int> &parent, vector<int> &rank)
{
    int pi = find(i, parent);
    int pj = find(j, parent);
    if (pi == pj)
        return;
    if (rank[pi] > rank[pj])
    {
        parent[pj] = pi;
    }
    else if (rank[pi] < rank[pj])
    {
        parent[pi] = pj;
    }
    else
    {
        parent[pi] = pj;
        ++rank[pj];
    }
}

// 最小生成树的kruskal算法，思想就是把所有边从小到大排序，不断拿最小的边来判断
// 加上这条边会不会有环，判断是否有环需要使用并查集，判断边的两个顶点是否处于同一个集合/find返回的根结点是否相同
void kruskal(vector<vector<int>> &graph)
{
    int ans = 0, edge_num = 0, size = graph.size();
    vector<int> parent(size, 0), rank(size, 0);
    for (int i = 0; i < size; ++i)
    {
        parent[i] = i;
    }

    // 制造优先队列
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> queue;
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            queue.push({graph[i][j], {i, j}});
        }
    }

    // 最小生成树的kruskal算法，需要找到顶点数-1条边结束
    while (edge_num != size - 1)
    {
        auto [weight, spot] = queue.top();
        queue.pop();
        if (find(spot.first, parent) != find(spot.second, parent))
        {
            ans += weight;
            ++edge_num;
            my_union(spot.first, spot.second, parent, rank);
        }
    }
    printf("weights:%d\n", ans);
}

int main(int argc, char *argv[])
{
    // 5个顶点的无向图，0表示无边，邻接矩阵
    vector<vector<int>> graph = {
        //   0     1     2     3     4
        {0, 1, 3, INT_MAX, INT_MAX}, // 0
        {1, 0, 1, 4, INT_MAX},       // 1
        {3, 1, 0, 1, 5},             // 2
        {INT_MAX, 4, 1, 0, 2},       // 3
        {INT_MAX, INT_MAX, 5, 2, 0}, // 4
    };
    kruskal(graph);
    return 0;
}