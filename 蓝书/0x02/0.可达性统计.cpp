#include <iostream>
#include <cstring>
#include <bitset>

using namespace std;

const int N = 30010;
int n, m;
int h[N], e[N], ne[N], deg[N], idx;
int q[N];
bitset<N> f[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
    deg[b] ++ ;
}
void topsort()
{
    int hh = 1, tt = 0;
    for (int i = 1; i <= n; i ++ )
        if (!deg[i])
            q[ ++ tt] = i;
    while (hh <= tt)
    {
        int x = q[hh ++ ];
        for (int i = h[x]; ~i; i = ne[i])
        {
            int y = e[i];
            if ( -- deg[y] == 0)
                q[ ++ tt] = y;
        }
    }
}
int main()
{
    memset(h, -1, sizeof(h));
    scanf("%d%d", &n, &m);
    while (m -- )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    topsort();
    for (int i = n; i; i -- )
    {
        int x = q[i];
        f[x][x] = 1;
        for (int i = h[x]; ~i; i = ne[i])
        {
            int y = e[i];
            f[x] |= f[y];
        }
    }
    for (int i = 1; i <= n; i ++ ) printf("%d\n", f[i].count());
    return 0;
}