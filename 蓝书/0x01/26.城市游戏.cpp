#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010, INF = 1e9;

int n, m;
int g[N][N], height[N], stk[N], tt;
int l[N], r[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= m; j ++ )
        {
            char ch; cin >> ch;
            if (ch == 'F') g[i][j] = 1;
        }
    }
    int res = 0;
    height[0] = height[m + 1] = -1;
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = 1; j <= m; j ++ )
        {
            if (g[i][j]) height[j] ++ ;
            else height[j] = 0;
        }
        tt = 0; stk[tt] = 0;
        for (int j = 1; j <= m; j ++ )
        {
            while (height[stk[tt]] >= height[j]) tt -- ;
            l[j] = stk[tt];
            stk[ ++ tt] = j;
        }
        tt = 0; stk[tt] = m + 1;
        for (int j = m; j; j -- )
        {
            while (height[stk[tt]] >= height[j]) tt -- ;
            r[j] = stk[tt];
            stk[ ++ tt] = j;
        }
        for (int j = 1; j <= m; j ++ )
            res = max(res, height[j] * (r[j] - l[j] - 1));
    }
    printf("%d\n", 3 * res);
    return 0;
}