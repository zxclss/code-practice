#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int N = 2510;

int n, m;
struct Seg
{
    int l, r;
    bool operator< (const Seg& t) const
    {
        return r < t.r;
    }
}seg[N];
map<int, int> spfs;

int main()
{
    cin >> n >> m;
    spfs[1001] = n; //边界处理最大情况
    for (int i = 0; i < n; i ++ ) cin >> seg[i].l >> seg[i].r;
    for (int i = 0, x, t; i < m; i ++ )
    {
        cin >> x >> t;
        spfs[x] += t;
    }
    sort(seg, seg + n);
    int res = 0;
    for (int i = 0; i < n; i ++ )
    {
        auto spf = spfs.lower_bound(seg[i].l);
        if (spf -> first <= seg[i].r)
        {
            res ++ ;
            if ( -- spf -> second == 0)
            {
                spfs.erase(spf);
            }
        }
    }
    cout << res << endl;
    return 0;
}