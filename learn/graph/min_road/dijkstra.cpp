#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
int dijkstra(vector<vector<int>> &graph, int start)
{
    int n = graph.size(), visited_num = 0;
    vector<int> cost(n, INT_MAX);
    cost[start] = 0;
    vector<bool> visited(n, 0);
    priority_queue<PII, vector<PII>, greater<>> queue;
    queue.push({0, 0});
    while (!queue.empty())
    {
        auto [weight, spot] = queue.top();
        queue.pop();
        if (visited[spot])
            continue;
        visited[spot] = 1;
        ++visited_num;
        for (int i = 0; i < n; ++i)
        {
            if (graph[spot][i] != INT_MAX && cost[i] > cost[spot] + graph[spot][i])
            {
                cost[i] = cost[spot] + graph[spot][i];
                queue.push({cost[i], i});
            }
        }
    }
    for (const auto &temp : cost)
    {
        printf("%d\n", temp);
    }
    return visited_num == n;
}

int main()
{
    vector<vector<int>> graph = {
        {0, 1, 3, INT_MAX, INT_MAX},
        {1, 0, 1, 4, INT_MAX},
        {3, 1, 0, 1, 5},
        {INT_MAX, 4, 1, 0, 2},
        {INT_MAX, INT_MAX, 5, 2, 0},
    };
    dijkstra(graph, 0);
    return 0;
}