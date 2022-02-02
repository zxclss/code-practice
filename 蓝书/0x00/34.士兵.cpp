#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010;

int n, res;
int x[N], y[N];

int calc(int a[])
{
    int res = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i ++ ) res += abs(a[i] - a[n + 1 >> 1]);
    return res;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> x[i] >> y[i];
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i ++ ) x[i] = x[i] - i + 1;
    cout << calc(x) + calc(y) << endl;
    return 0;
}