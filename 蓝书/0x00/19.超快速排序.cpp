#include <iostream>

using namespace std;

const int N = 5e5 + 10;

int n;
int a[N], b[N];

long long cal_revpair(int l, int r)
{
    if (l == r) return 0;
    
    int mid = (l + r) >> 1;
    long long cnt = cal_revpair(l, mid) + cal_revpair(mid + 1, r);
    
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
    while (cin >> n, n)
    {
        for (int i = 0; i < n; i ++ ) cin >> a[i];
        cout << cal_revpair(0, n - 1) << endl;
    }
    return 0;
}