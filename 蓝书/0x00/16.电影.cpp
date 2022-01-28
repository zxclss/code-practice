#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;

int n, m;
int a[N], b[N], c[N], cnt[N * 3];
vector<int> xs;

void discrete()
{
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
}
int query(int x)
{
    return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i], xs.push_back(a[i]);
    cin >> m;
    for (int i = 1; i <= m; i ++ ) cin >> b[i], xs.push_back(b[i]);
    for (int i = 1; i <= m; i ++ ) cin >> c[i], xs.push_back(c[i]);
    discrete();
    for (int i = 1; i <= n;i ++ )
    {
        int x = query(a[i]);
        cnt[x] ++ ;
    }
    int s1 = 0, s2 = 0, res = 1;
    for (int i = 1; i <= m; i ++ )
    {
        int x1 = query(b[i]), x2 = query(c[i]);
        if (cnt[x1] > s1) s1 = cnt[x1], s2 = cnt[x2], res = i;
        else if (cnt[x1] == s1 && cnt[x2] > s2) s2 = cnt[x2], res = i;
    }
    cout << res << endl;
    return 0;
}