#include <iostream>

using namespace std;

const int N = 250010;

int n, m;
int a[N], b[N];

long long cal_revpair(int a[], int l, int r)
{
    if (l >= r) return 0;

    int mid = (l + r) >> 1;
    long long cnt = cal_revpair(a, l, mid) + cal_revpair(a, mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (a[i] > a[j]) cnt += mid - i + 1, b[k ++ ] = a[j ++ ];
        else b[k ++ ] = a[i ++ ];
    }
    while (i <= mid) b[k ++ ] = a[i ++ ];
    while (j <= r) b[k ++ ] = a[j ++ ];

    for (int i = 0; i < k; i ++ ) a[l + i] = b[i];
    return cnt;
}
int main()
{
    while (cin >> n)
    {
        n *= n;
        for (int i = 0, t, d = 0; i < n; i ++ )
        {
            cin >> t;
            if (t) a[d ++ ] = t;
        }
        int s1 = cal_revpair(a, 0, n - 2) & 1;
        for (int i = 0, t, d = 0; i < n; i ++ )
        {
            cin >> t;
            if (t) a[d ++ ] = t;
        }
        int s2 = cal_revpair(a, 0, n - 2) & 1;
        puts(s1 ^ s2 ? "NIE" : "TAK");
    }
    return 0;
}