#include <iostream>
#include <algorithm>
#include <vector>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 510, M = N << 1;

int n, m;
int s[M][M];
vector<int> xs;
PII points[N];

void discrete()
{
    xs.push_back(0);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
}
int get(int val)
{
    return lower_bound(xs.begin(), xs.end(), val) - xs.begin();
}
bool check(int len)
{
    for (int x2 = 1, x1 = 0; x2 < xs.size(); x2 ++ )
    {
        while (x1 <= x2 && xs[x2] - xs[x1 + 1] + 1 > len) x1 ++ ;
        for (int y2 = 1, y1 = 0; y2 < xs.size(); y2 ++ )
        {
            while (y1 <= y2 && xs[y2] - xs[y1 + 1] + 1 > len) y1 ++ ;
            if (s[x2][y2] - s[x1][y2] - s[x2][y1] + s[x1][y1] >= m)
                return true;
        }
    }
    return false;
}
int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; i ++ )
    {
        int x, y; cin >> x >> y;
        xs.push_back(x);
        xs.push_back(y);
        points[i] = {x, y};
    }
    discrete();
    for (int i = 0; i < n; i ++ )
    {
        int x = get(points[i].x), y = get(points[i].y);
        s[x][y] ++ ;
    }
    for (int i = 1; i < xs.size(); i ++ )
        for (int j = 1; j < xs.size(); j ++ )
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    int l = 1, r = 10000;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid; else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}