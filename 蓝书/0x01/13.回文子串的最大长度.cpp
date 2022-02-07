#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

const int SIZE = 2e6 + 10;
const int P = 13331;

int n;
char s[SIZE];
ULL f[SIZE], g[SIZE], p[SIZE];

// g[i] = s[n+1-i ... n]
// hr(i, j) = get(g, n+1-j, n+1-i)

void initialize()
{
    p[0] = 1;
    f[0] = g[n + 1] = 0;
    for (int i = 1, j = n; i <= n; i ++ , j -- )
    {
        p[i] = p[i - 1] * P;
        f[i] = f[i - 1] * P + s[i];
        g[i] = g[i - 1] * P + s[j];
    }
}
ULL get_hash(ULL h[], int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}
void solve()
{
    n = strlen(s + 1);
    for (int i = n << 1; i; i -= 2)
    {
        s[i] = s[i / 2];
        s[i - 1] = '#';
    }
    n <<= 1;
    initialize();

    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int l = 0, r = min(i - 1, n - i);
        while (l < r)   //[i - mid, i] [i, i + mid] -> [n+1-(i+mid), n+1-i]
        {
            int mid = (l + r + 1) >> 1;
            ULL lval = get_hash(f, i - mid, i);
            ULL rval = get_hash(g, n + 1 - (i + mid), n + 1 - i);
            if (lval == rval) l = mid; else r = mid - 1;
        }
        if (s[i - l] != '#') l ++ ;
        res = max(res, l);
    }
    printf("%d\n", res);
}
int main()
{
    int T = 1;
    while (scanf("%s", s + 1), strcmp(s + 1, "END"))
    {
        printf("Case %d: ", T ++ );
        solve();
    }
    return 0;
}