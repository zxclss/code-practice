#include <iostream>
#include <algorithm>

using namespace std;

const int N = 50010, INF = 1e9;

int n;
struct Cow
{
    int w, s;
    bool operator< (const Cow& t) const
    {
        return s + w < t.w + t.s;
    }
}cows[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> cows[i].w >> cows[i].s;
    sort(cows + 1, cows + n + 1);
    int prefix_w = 0, res = -INF;
    for (int i = 1; i <= n; i ++ )
    {
        res = max(res, prefix_w - cows[i].s);
        prefix_w += cows[i].w;
    }
    cout << res << endl;
    return 0;
}