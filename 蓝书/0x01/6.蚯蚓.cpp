#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 8e6 + 10;

int n, m, q, u, v, t;
int qx[N], ql[N], qr[N];
int hhx, ttx = -1, hhl, ttl = -1, hhr, ttr = -1;

int get_max()
{
    int x = -1e9;
    if (hhx <= ttx) x = max(x, qx[hhx]);
    if (hhl <= ttl) x = max(x, ql[hhl]);
    if (hhr <= ttr) x = max(x, qr[hhr]);
    if (hhx <= ttx && x == qx[hhx]) hhx ++ ;
    else if (hhl <= ttl && x == ql[hhl]) hhl ++ ;
    else hhr ++ ;
    return x;
}
int main()
{
    scanf("%d%d%d%d%d%d", &n, &m, &q, &u, &v, &t);

    for (int i = 0; i < n; i ++ ) scanf("%d", &qx[i]);
    sort(qx, qx + n, greater<int>());
    ttx = n - 1;

    int delta = 0;
    for (int i = 1; i <= m; i ++ )
    {
        int x = get_max() + delta;
        delta += q;
        if (i % t == 0) printf("%d ", x);
        int templ = x * 1ll * u / v;
        int tempr = x - templ;
        templ -= delta, tempr -= delta;
        ql[ ++ ttl] = templ, qr[ ++ ttr] = tempr;
    }
    puts("");

    for (int i = 1; i <= n + m; i ++ )
    {
        int x = get_max();
        if (i % t == 0) printf("%d ", x + delta);
    }
    puts("");
    return 0;
}