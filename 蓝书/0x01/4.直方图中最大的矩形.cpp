#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N], l[N], r[N], q[N], tt;

int main()
{
    while (cin >> n, n)
    {
        a[0] = a[n + 1] = -1;
        for (int i = 1; i <= n; i ++ ) cin >> a[i];
        tt = 0, q[tt] = 0;
        for (int i = 1; i <= n; i ++ )
        {
            while (a[i] <= a[q[tt]]) tt -- ;
            l[i] = q[tt];
            q[ ++ tt] = i;
        }
        tt = 0, q[tt] = n + 1;
        for (int i = n; i; i -- )
        {
            while (a[i] <= a[q[tt]]) tt -- ;
            r[i] = q[tt];
            q[ ++ tt] = i;
        }
        long long res = 0;
        for (int i = 1; i <= n; i ++ )
            res = max(res, (long long) a[i] * (r[i] - l[i] - 1));
        cout << res << endl;
    }
    return 0;
}