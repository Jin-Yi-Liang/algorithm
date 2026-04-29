// 多源最短路径-floyd
#include <bits/stdc++.h>
using namespace std;
#define INF 1e7
int N, M, Q;
int min_dis[205][205];
int build_time[205];
int cnt;

void update(int k)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            min_dis[i][j] = min(min_dis[i][j], min_dis[i][k] + min_dis[k][j]);
        }
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            min_dis[i][j] = INF;
        }
    }
    for (int i = 0; i < N; ++i)
    {
        cin >> build_time[i];
        min_dis[i][i] = 0;
    }
    for (int i = 0; i < M; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        min_dis[u][v] = w;
        min_dis[v][u] = w;
    }

    cin >> Q;
    for (int i = 0; i < Q; ++i)
    {
        int qu, qv, qw;
        cin >> qu >> qv >> qw;
        while (cnt<N && qw >= build_time[cnt])
        {
            update(cnt);
            ++cnt;
        }
        if(build_time[qu]>qw || build_time[qv]>qw || min_dis[qu][qv]==INF)
            printf("-1\n");
        else
            printf("%d\n",min_dis[qu][qv]);
    }

    return 0;
}