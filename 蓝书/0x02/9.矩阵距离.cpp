#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010;

int n, m;
int d[N][N];
char g[N][N];

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
bool valid(int x, int y)
{
    return x && x <= n && y && y <= m;
}
int bfs()
{
    memset(d, -1, sizeof d);
    queue<PII> q;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            if (g[i][j] == '1')
                q.push({i, j}), d[i][j] = 0;
    while (q.size())
    {
        PII top = q.front(); q.pop();
        for (int i = 0; i < 4; i ++ )
        {
            int x = top.x + dx[i], y = top.y + dy[i];
            if (!valid(x, y)) continue;
            if (~d[x][y]) continue;
            d[x][y] = d[top.x][top.y] + 1;
            q.push({x, y});
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%s", g[i] + 1);
    bfs();
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= m; j ++ )
        {
            printf("%d ", d[i][j]);
        }
        puts("");
    }
    return 0;
}