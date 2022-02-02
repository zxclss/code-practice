#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n;
struct Seg
{
    int l, r;
    bool operator< (const Seg& t) const
    {
        return l * r < t.l * t.r;
    }
}seg[N];

vector<int> mul(vector<int> a, int b)
{
    vector<int> res;
    int t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += a[i] * b;
        res.push_back(t % 10);
        t /= 10;
    }
    while (t) res.push_back(t % 10), t /= 10;
    return res;
}
vector<int> div(vector<int> a, int b)
{
    vector<int> res;
    int t = 0;
    for (int i = a.size() - 1; i >= 0; i -- )
    {
        t = t * 10 + a[i];
        res.push_back(t / b);
        t %= b;
    }
    reverse(res.begin(), res.end());
    while (res.size() > 1 && res.back() == 0) res.pop_back();
    return res;
}
bool lw(vector<int>& a, vector<int>& b)
{
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i -- )
        if (a[i] != b[i])
            return a[i] < b[i];
    return false;
}
int main()
{
    cin >> n;
    for (int i = 0; i <= n; i ++ ) cin >> seg[i].l >> seg[i].r;
    sort(seg + 1, seg + n + 1);
    vector<int> prefix = {seg[0].l}, res;
    for (int i = 1; i <= n; i ++ )
    {
        vector<int> t = div(prefix, seg[i].r);
        if (lw(res, t)) res = t;
        prefix = mul(prefix, seg[i].l);
    }
    for (int i = res.size() - 1; i >= 0; i -- ) cout << res[i];
    cout << endl;
    return 0;
}