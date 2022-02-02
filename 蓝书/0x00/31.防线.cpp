#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int n;
int s[N], e[N], d[N];

int calc(int limit)
{
    int res = 0;
    for (int i = 1; i <= n; i ++ )
        if (s[i] <= limit)
            res += (min(e[i], limit) - s[i]) / d[i] + 1;
    return res;
}
void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> s[i] >> e[i] >> d[i];
    int l = 1, r = (1 << 31) - 1;
    while (l < r)
    {
        int mid = ((long long) l + r) >> 1;
        if (calc(mid) & 1) r = mid; else l = mid + 1;
    }
    if (calc(l) & 1 ^ 1) puts("There's no weakness.");
    else cout << l << " " << calc(l) - calc(l - 1) << endl;
}
int main()
{
    int T;
    cin >> T;
    while (T -- ) solve();
    return 0;
}