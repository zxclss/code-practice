#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1e5 + 10;
const double INF = 1e10;

int n;
struct Point
{
    double x, y;
    int type;
    bool operator <(const Point &t) const
    {
        return x < t.x;
    }
    bool operator ==(const Point &t) const
    {
        return x == t.x && y == t.y && type == t.type;
    }
} points[N], temp[N];

double get_dist(Point &a, Point & b)
{
    if (a.type == b.type) return INF;
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
double dfs(int l, int r)
{
    if (l >= r) return INF;
    int mid = (l + r) >> 1;
    int midx = points[mid].x;
    double res = min(dfs(l, mid), dfs(mid + 1, r));
    
    {
        int k = 0, i = l, j = mid + 1;
        while (i <= mid && j <= r)
            if (points[i].y < points[j].y) temp[k ++ ] = points[i ++ ];
            else temp[k ++ ] = points[j ++ ];
        while (i <= mid) temp[k ++ ] = points[i ++ ];
        while (j <= r) temp[k ++ ] = points[j ++ ];
        for (int i = 0; i < k; i ++ ) points[l + i] = temp[i];
    }
    
    int k = 0;
    for (int i = l; i <= r; i ++ )
        if (abs(points[i].x - midx) <= res)
            temp[k ++ ] = points[i];
    for (int i = 0; i < k; i ++ )
        for (int j = i - 1; ~j && temp[i].y - temp[j].y <= res; j -- )
            res = min(res, get_dist(temp[i], temp[j]));
    return res;
}
void solve()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
        cin >> points[i].x >> points[i].y,
        points[i].type = 0;
    for (int i = n; i < n << 1; i ++ )
        cin >> points[i].x >> points[i].y,
        points[i].type = 1;
    n <<= 1;
    sort(points, points + n );
    n = unique(points, points + n) - points;
    printf("%.3lf\n", dfs(0, n - 1));
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T -- ) solve();
    return 0;
}