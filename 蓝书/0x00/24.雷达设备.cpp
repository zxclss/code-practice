#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1010;
const double eps = 1e-6;

int n, d;
struct Seg
{
    double l, r;
    bool operator<(const Seg& t) const
    {
        return r < t.r;
    }
}seg[N];

int main()
{
    cin >> n >> d;
    
    bool success = true;
    
    for (int i = 1; i <= n; i ++ )
    {
        int x, y;
        cin >> x >> y;
        if (y > d) success = false;
        double dx = sqrt(d * d - y * y);
        seg[i] = {x - dx, x + dx};
    }
    if (!success) cout << -1 << endl;
    else
    {
        int res = 0;
        sort(seg + 1, seg + n + 1);
        double pos = -1e9;
        for (int i = 1; i <= n; i ++ )
        {
            if (pos + eps < seg[i].l)
            {
                res ++ ;
                pos = seg[i].r;
            }
        }
        cout << res << endl;
    }
    return 0;
}