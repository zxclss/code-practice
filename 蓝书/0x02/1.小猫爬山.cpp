#include <iostream>
#include <algorithm>

using namespace std;

const int N = 20;

int n, m;
int c[N], cab[N], res = N;

void dfs(int now, int cnt)
{
    if (cnt >= res) return;
    if (now == n + 1)
    {
        res = cnt;
        return;
    }
    for (int i = 1; i <= cnt; i ++ )
    {
        if (cab[i] + c[now] <= m)
        {
            cab[i] += c[now];
            dfs(now + 1, cnt);
            cab[i] -= c[now];
        }
    }
    cab[cnt + 1] = c[now];
    dfs(now + 1, cnt + 1);
    cab[cnt + 1] = 0;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &c[i]);
    sort(c + 1, c + n + 1, greater<int>());
    dfs(1, 0);
    printf("%d\n", res);
    return 0;
}