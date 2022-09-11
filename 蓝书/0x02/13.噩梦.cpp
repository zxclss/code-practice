#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 810;

int n, m;
char g[N][N];
int st[N][N];
PII boy, girl, ghost[2];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool check(int a, int b, int t)
{
    if (a < 0 || a >= n || b < 0 || b >= m || g[a][b] == 'X') return false;
    for (int i = 0; i < 2; i ++ )
        if (abs(ghost[i].x - a) + abs(ghost[i].y - b) <= 2 * t)
            return false;
    return true;
}
int solve()
{
    memset(st, 0, sizeof st);
    cin >> n >> m;
    for (int i = 0; i < n; i ++ ) cin >> g[i];
    int cnt = 0;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ )
            if (g[i][j] == 'M') boy = {i, j};
            else if (g[i][j] == 'G') girl = {i, j};
            else if (g[i][j] == 'Z') ghost[cnt ++ ] = {i, j};
    
    queue<PII> qb, qg;
    qb.push(boy);
    qg.push(girl);

    int step = 0;
    while (qb.size() || qg.size())
    {
        step ++ ;
        for (int i = 0; i < 3; i ++ )
        {
            for (int j = 0, siz = qb.size(); j < siz; j ++ )
            {
                PII t = qb.front(); qb.pop();
                int x = t.x, y = t.y;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; k ++ )
                {
                    int a = x + dx[k], b = y + dy[k];
                    if (check(a, b, step))
                    {
                        if (st[a][b] == 2) return step;
                        if (!st[a][b])
                        {
                            st[a][b] = 1;
                            qb.push({a, b});
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 1; i ++ )
        {
            for (int j = 0, siz = qg.size(); j < siz; j ++ )
            {
                PII t = qg.front(); qg.pop();
                int x = t.x, y = t.y;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; k ++ )
                {
                    int a = x + dx[k], b = y + dy[k];
                    if (check(a, b, step))
                    {
                        if (st[a][b] == 1) return step;
                        if (!st[a][b])
                        {
                            st[a][b] = 2;
                            qg.push({a, b});
                        }
                    }
                }
            }
        }
    }
    return -1;
}
int main()
{
    int T;
    cin >> T;
    while (T -- ) cout << solve() << endl;
    return 0;
}