/*
shortest path from src to every other node
Helps to detect negative cycle
Only works for directed graph

Relax all the edges n-1 times sequentially
Relax: dist[u] + wght < dist[v]

Why n-1 times?
Because in worst case that will traverse all the edges for relaxation
On nth iteration still relaxation will be done in case of negative cycle - distance will be reduced -> means it's a negative cycle

T.C - O(V*E) more time than dijkstra
*/

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vector<pii>> vvpii;

vi bellmanFord(int v, vvi &edges, int src)
{
    vi dist(v, 1e9);
    dist[src] = 0;

    int e = edges.size();
    for (int i = 0; i < v - 1; i++)
    {
        for (int it = 0; it < e; it++)
        {
            int u = edges[it][0], v = edges[it][1], wght = edges[it][2];
            if (dist[u] + wght < dist[v])
            {
                dist[v] = dist[u] + wght;
            }
        }
    }

    // nth relaxation to check for negative cycles
    for (int it = 0; it < e; it++)
    {
        int u = edges[it][0], v = edges[it][1], wght = edges[it][2];
        if (dist[u] + wght < dist[v])
        {
            return {-1};
        }
    }

    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}