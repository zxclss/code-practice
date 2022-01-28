#include <iostream>
#include <cstring>

using namespace std;

const int N = 10;

int n = 5;
int dx[5] = {0, -1, 0, 1, 0};
int dy[5] = {0, 0, 1, 0, -1};
char g[N][N], b[N][N];

void turn(int i, int j)
{
    for (int d = 0; d < 5; d ++ )
    {
        int x = i + dx[d], y = j + dy[d];
        if (x < 0 || x >= n || y < 0 || y >= n) continue;
        g[x][y] ^= 1;
    }
}
void solve()
{
    for (int i = 0; i < n; i ++ ) cin >> b[i];

    int res = -1;
    for (int op = 0, cnt; cnt = 0, op < 1 << n; op ++ )
    {
        memcpy(g, b, sizeof g);
        for (int i = 0; i < n; i ++ )
            if (op >> i & 1)
                turn(0, i), cnt ++ ;
        for (int i = 1; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                if (g[i - 1][j] == '0')
                    turn(i, j), cnt ++ ;
        if (cnt > 6) continue;
        bool flag = true;
        for (int i = 0; i < n; i ++ )
            if (g[n - 1][i] == '0')
                flag = false;
        if (flag && (res == -1 || res > cnt))
            res = cnt;
    }
    cout << res << endl;
}
int main()
{
    int T = 1; cin >> T;
    while (T -- )
    {
        solve();
    }
    return 0;
}