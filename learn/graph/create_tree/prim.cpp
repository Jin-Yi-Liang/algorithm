#include <bits/stdc++.h>
using namespace std;

void prim(vector<vector<int>> &graph, int start)
{
    int num = graph.size();
    int ans = 0, visited_num = 0;
    vector<int> cost(num, INT_MAX), from(num, -1);
    vector<bool> visited(num, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> queue{};
    queue.push({0, start});

    while (visited_num != num)
    {
        auto [weight, cur] = queue.top();
        queue.pop();
        if (visited[cur] == 1)
            continue;
        visited[cur] = 1;
        ++visited_num;
        ans += weight;
        for (int i = 0; i < num; ++i)
        {
            if (visited[i] == 0 && graph[cur][i] < cost[i])
            {
                cost[i] = graph[cur][i];
                from[i] = cur;
                queue.push({cost[i], i});
            }
        }
    }
    printf("weights:%d\n", ans);
    for (int i = 0; i < num; ++i)
    {
        printf("%d-%d\n", i, from[i]);
    }
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
    prim(graph, 0);
    return 0;
}