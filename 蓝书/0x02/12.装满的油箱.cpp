#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

const int INF = 0x3f3f3f3f;

int n, m, q;
int C, S, E;
int h[1010], e[20010], w[20010], ne[20010], idx;
int p[1010];
int dist[1010][110];
bool st[1010][110];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
int dijkstra()
{
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    dist[S][0] = 0;
    heap.push({0, {S, 0}});
    while (heap.size())
    {
        auto t = heap.top(); heap.pop();
        int cost = t.x, ver = t.y.x, fuel = t.y.y;
        
        if (st[ver][fuel]) continue;
        st[ver][fuel] = true;
        if (ver == E) return cost;
        
        if (fuel < C && dist[ver][fuel + 1] > cost + p[ver])
        {
            dist[ver][fuel + 1] = cost + p[ver];
            heap.push({cost + p[ver], {ver, fuel + 1}});
        }
        for (int i = h[ver]; ~i; i = ne[i])
        {
            int j = e[i], d = w[i];
            if (fuel >= d && dist[j][fuel - d] > cost)
            {
                dist[j][fuel - d] = cost;
                heap.push({cost, {j, fuel - d}});
            }
        }
    }
    return -1;
}
int main()
{
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 0; i < n; i ++ ) cin >> p[i];
    for (int i = 0; i < m; i ++ )
    {
        int u, v, d;
        cin >> u >> v >> d;
        add(u, v, d), add(v, u, d);
    }
    cin >> q;
    while (q -- )
    {
        cin >> C >> S >> E;
        int t = dijkstra();
        if (~t) cout << t << endl;
        else puts("impossible");
    }
    return 0;
}