#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N], b[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    for (int i = 2; i <= n; i ++ ) b[i] = a[i] - a[i - 1];
    
    long long p = 0, q = 0;
    for (int i = 2; i <= n; i ++ )
    {
        if (b[i] > 0) p += b[i];
        else if (b[i] < 0) q -= b[i];
    }
    cout << max(p, q) << endl << abs(p - q) + 1 << endl;
    return 0;
}