#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 5e5 + 10;

int n, m;
LL T;
int a[N], b[N], t[N];

bool check(int l, int mid, int r)
{
    for (int i = mid; i < r; i ++ ) b[i] = a[i];
    sort(b + mid, b + r);
    int i = l, j = mid, k = 0;
    while (i < mid && j < r)
    {
        if (b[i] < b[j]) t[k ++ ] = b[i ++ ];
        else t[k ++ ] = b[j ++ ];
    }
    while (i < mid) t[k ++ ] = b[i ++ ];
    while (j < r) t[k ++ ] = b[j ++ ];
    
    LL sum = 0;
    for (int i = 0; i < m && i < k; i ++ , k -- )
        sum += (LL) (t[i] - t[k - 1]) * (t[i] - t[k - 1]);
    return sum <= T;
}
void solve()
{
    scanf("%d%d%lld", &n, &m, &T);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);
    int l = 0, cnt = 0;
    while (l < n)
    {
        int p = 1, r = l;
        while (p)
        {
            if (r + p <= n && check(l, r, r + p))
            {
                r += p;
                p *= 2;
                for (int i = l; i < r; i ++ )
                    b[i] = t[i - l];
            }
            else p /= 2;
        }
        cnt ++ ;
        l = r;
    }
    printf("%d\n", cnt);
}
int main()
{
    int K;
    scanf("%d", &K);
    while (K -- )
    {
        solve();
    }
    return 0;
}