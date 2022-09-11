#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

const int N = 1010, M = 20010;

int S, T, K, n, m;
int hp[N], hn[N], e[M], w[M], ne[M], idx;
int cnt[N], dist[N];
bool st[N];

void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
void dijkstra()
{
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    dist[T] = 0;
    heap.push({0, T});
    while (heap.size())
    {
        PII t = heap.top(); heap.pop();
        
        if (st[t.y]) continue;
        st[t.y] = true;

        for (int i = hn[t.y]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t.y] + w[i])
            {
                dist[j] = dist[t.y] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}
int f(int id)
{
    return dist[id];
}
int astar()
{
    memset(cnt, 0, sizeof cnt);
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    heap.push({f(S), {0, S}});
    while (heap.size())
    {
        PIII t = heap.top(); heap.pop();

        int ver = t.y.y, d = t.y.x;
        cnt[ver] ++ ;
        if (cnt[T] == K) return d;
        
        for (int i = hp[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if (cnt[j] < K)
                heap.push({d + w[i] + f(j), {d + w[i], j}});
        }
    }
    return -1;
}
int main()
{
    cin >> n >> m;
    memset(hp, -1, sizeof hp);
    memset(hn, -1, sizeof hn);
    while (m -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(hp, a, b, c);
        add(hn, b, a, c);
    }
    cin >> S >> T >> K;
    if (S == T) K ++ ;
    
    dijkstra();
    cout << astar() << endl;
    return 0;
}