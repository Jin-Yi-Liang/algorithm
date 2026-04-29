#include <bits/stdc++.h>
using namespace std;

struct EDGE
{
    int start, end, weight;
};

void ford(int n, int start, vector<EDGE> &edge)
{
    vector<int> cost(n + 1, INT_MAX);
    cost[start] = 0;
    int m = edge.size();
    for (int i = 0; i < n - 1; ++i)
    {
        bool exec = false;
        for (int j = 0; j < m; ++j)
        {
            int u = edge[j].start, v = edge[j].end, w = edge[j].weight;
            if (cost[u] != INT_MAX && cost[u] + w < cost[v])
            {
                cost[v] = cost[u] + w;
                exec = true;
            }
        }
        if (!exec)
            break;
    }
    bool exec = false;
    for (int j = 0; j < m; ++j)
    {
        int u = edge[j].start, v = edge[j].end, w = edge[j].weight;
        if (cost[u] != INT_MAX && cost[u] + w < cost[v])
        {
            exec = true;
            break;
        }
    }
    if (exec)
    {
        cout << "has negative loop" << endl;
        return;
    }
    for (int i = 1; i <= n; ++i)
    {
        if (cost[i] == INT_MAX)
            cout << "INF ";
        else
            cout << cost[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<EDGE> edge;
    EDGE temp;
    for (int i = 0; i < m; ++i)
    {
        cin >> temp.start >> temp.end >> temp.weight;
        edge.push_back(temp);
    }
    int start;
    cin >> start;
    ford(n, start, edge);

    return 0;
}