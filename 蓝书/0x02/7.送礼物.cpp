#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;

const int N = 50, M = N / 2;

int n, w, mid, g[N], a[1 << M], al;
int res;

//正向深搜，指数型枚举，记录所有的边界状态值
void dfs1(int dep, LL cur_w)
{
    if (cur_w > w) return;
    if (dep > mid)
    {
        a[ ++ al] = (int)cur_w;
        return;
    }
    dfs1(dep + 1, cur_w + g[dep]);
    dfs1(dep + 1, cur_w);
}
//逆向深搜，指数型枚举，搜到问题状态空间的边界时，二分正向搜素的最大匹配值
void dfs2(int dep, LL cur_w)
{
    if (cur_w > w) return;
    if (dep > n)
    {
        int l = 1, r = al;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (cur_w + a[mid] <= w) l = mid; else r = mid - 1;
        }
        res = max(res, (int)cur_w + a[r]);
        return;
    }
    dfs2(dep + 1, cur_w + g[dep]);
    dfs2(dep + 1, cur_w);
}
int main()
{
    scanf("%d%d", &w, &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &g[i]);

    // 优化搜索顺序
    sort(g + 1, g + n + 1);
    reverse(g + 1, g + n + 1);
    // 切分中点，双向搜索
    mid = (n + 1) >> 1;
    // 正向深搜
    dfs1(1, 0ll);
    // 排序去重起点所在的状态空间连通块边界点的值
    sort(a + 1, a + al + 1);
    al = unique(a + 1, a + al + 1) - a - 1;
    // 逆向深搜
    dfs2(mid + 1, 0ll);

    printf("%d\n", res);
    return 0;
}