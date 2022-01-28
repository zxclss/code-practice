#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int n, m, t;
int row[N], col[N];
long long s[N], a[N];

long long calc(int c[], int n)
{
    int avg = t / n;
    for (int i = 1; i <= n; i ++ ) a[i] = c[i] - avg;
    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + a[i];
    sort(s + 1, s + n + 1);
    long long res = 0;
    for (int i = 1; i <= n; i ++ ) res += abs(s[i] - s[(n + 1) / 2]);
    return res;
}
int main()
{
    cin >> n >> m >> t;
    for (int i = 1; i <= t; i ++ )
    {
        int x, y;
        cin >> x >> y;
        row[x] ++ , col[y] ++ ;
    }
    if (t % n == 0 && t % m == 0)
    {
        cout << "both " << calc(row, n) + calc(col, m) << endl;
    }
    else if (t % n == 0)
    {
        cout << "row " << calc(row, n) << endl;
    }
    else if (t % m == 0)
    {
        cout << "column " << calc(col, m) << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
    return 0;
}