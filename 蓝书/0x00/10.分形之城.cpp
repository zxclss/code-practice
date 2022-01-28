#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

double get_dist(PLL a, PLL b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
PLL calc(int n, LL m)
{
    if (!n) return {0, 0};
    LL len = 1ll << (n - 1), cnt = 1ll << (2 * n - 2);
    PLL pos = calc(n - 1, m % cnt);
    LL x = pos.x, y = pos.y;
    LL z = m / cnt;
    if (z == 0) return {y, x};
    if (z == 1) return {x, y + len};
    if (z == 2) return {x + len, y + len};
    if (z == 3) return {2 * len - 1 - y, len - 1 - x};
}
void solve()
{
    LL n, a, b;
    cin >> n >> a >> b;
    PLL a_pose = calc(n, -- a);
    PLL b_pose = calc(n, -- b);
    printf("%.0lf\n", get_dist(a_pose, b_pose) * 10);
}
int main()
{
    int T = 1;
    cin >> T;
    while (T -- )
    {
        solve();
    }
    return 0;
}