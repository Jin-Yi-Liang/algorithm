// spfa 最短路径
#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
int n, m, start;
// 链式前向星
typedef struct
{
    int to, w, next;
} Edge;
Edge edge[20005];
int head[1005];
int cnt;
int min_dis[1005];
bool inQueue[1005];
queue<int> q;

void add_edge(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
    ++cnt;
}

void spfa(int start)
{
    for (int i = 0; i < n; ++i)
    {
        inQueue[i] = false;
        min_dis[i] = INF;
    }
    min_dis[start] = 0;
    q.push(start);
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        inQueue[u] = false;
        for (int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to, w = edge[i].w;
            if (min_dis[v] > min_dis[u] + w)
            {
                min_dis[v] = min_dis[u] + w;
                if (inQueue[v])
                    continue;
                q.push(v);
                inQueue[v] = true;
            }
        }
    }
}

int main()
{
    cin >> n >> m >> start;
    for (int i = 0; i < n; ++i)
        head[i] = -1;

    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }
    spfa(start);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", min_dis[i]);
    }

    return 0;
}