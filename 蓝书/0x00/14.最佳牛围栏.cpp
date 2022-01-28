#include <iostream>

using namespace std;

const int N = 1e5 + 10;
const double eps = 1e-5;

int n, m;
int a[N];
double s[N];

bool valid(double avg)
{
    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + a[i] - avg;
    double min_val = 0;
    for (int i = m; i <= n; i ++ )
    {
        min_val = min(min_val, s[i - m]);
        if (s[i] > min_val) return true;
    }
    return false;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    double l = 0, r = 2000;
    while (l + eps < r)
    {
        double mid = (l + r) / 2;
        if (valid(mid)) l = mid; else r = mid;
    }
    cout << (int)(r * 1000) << endl;
    return 0;
}