#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>

#define x first
#define y second

using namespace std;

typedef pair<int,int> PII;

const int N = 510;

int T, n, m;
char g[N][N];
int dist[N][N];
bool st[N][N];

void solve()
{
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[0][0] = 0;
    deque<PII> deq;
    deq.push_back({0, 0});

    char state[] = {"\\/\\/"};
    int dx[] = {1, 1, -1, -1}, dy[] = {1, -1, -1, 1};
    int ix[] = {0, 0, -1, -1}, iy[] = {0, -1, -1, 0};
    
    while (deq.size())
    {
        PII t = deq.front();
        deq.pop_front();
        if (st[t.x][t.y]) continue;
        if (t.x == n && t.y == m) break;
        st[t.x][t.y] = true;

        for (int i = 0; i < 4; i ++ )
        {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a > n || b < 0 || b > m) continue;
            int w = g[t.x + ix[i]][t.y + iy[i]] != state[i];
            int d = w + dist[t.x][t.y];
            
            if (d < dist[a][b])
            {
                dist[a][b] = d;
                if (w) deq.push_back({a, b});
                else deq.push_front({a, b});
            }
        }
    }
    cout << dist[n][m] << endl;
}
int main()
{
    cin >> T;
    while (T -- )
    {
        cin >> n >> m;
        for (int i = 0; i < n; i ++ ) cin >> g[i];
        if ((n + m) & 1) puts("NO SOLUTION");
        else solve();
    }
    return 0;
}