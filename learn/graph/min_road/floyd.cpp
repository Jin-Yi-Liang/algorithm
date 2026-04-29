#include <bits/stdc++.h>
using namespace std;

void print_path(int i, int j, vector<vector<int>> &from)
{
    if (i == j)
    {
        printf("%d", i);
        return;
    }
    print_path(i, from[i][j], from);
    printf(" -> %d", j);
}

void floyd(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<vector<int>> cost(n, vector<int>(n, INT_MAX));
    vector<vector<int>> from(n, vector<int>(n, -1));
    // 没有激活任何点的cost
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cost[i][j] = graph[i][j];
            if (cost[i][j] != INT_MAX)
                from[i][j] = i;
        }
    }

    // 不断加入激活点k，看是否有更加短的路径可以选择，i表示行、j表示列
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (cost[i][k] != INT_MAX && cost[k][j] != INT_MAX && cost[i][j] > cost[i][k] + cost[k][j])
                {
                    cost[i][j] = cost[i][k] + cost[k][j];
                    from[i][j] = from[k][j];
                }
            }
        }
    }

    // 输出结果
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cost[i][j] == INT_MAX ? printf("INT_MAX ") : printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------\n");

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", from[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------\n");

    // 打印所有最短路径
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d -> %d: ", i, j);
            if (cost[i][j] == INT_MAX)
            {
                printf("No path\n");
            }
            else
            {
                print_path(i, j, from);
                printf("\ncost: %d\n", cost[i][j]);
            }
        }
    }
}

int main()
{
    vector<vector<int>> graph = {
        {0, 5, INT_MAX, 10},
        {INT_MAX, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 1},
        {2, INT_MAX, INT_MAX, 0}};
    floyd(graph);
    return 0;
}