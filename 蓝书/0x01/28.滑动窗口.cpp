#include <iostream>

using namespace std;

const int N = 1e6 + 10, INF = 1e9;

int n, m;
int w[N], q[N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    // 最小值窗口
    {
        int hh = 0, tt = -1;
        for (int i = 1; i <= n; i ++ )
        {
            while (hh <= tt && w[q[tt]] >= w[i]) tt -- ;
            q[ ++ tt] = i;
            if (hh <= tt && i - q[hh] + 1 > m) hh ++ ;
            if (i >= m) printf("%d ", w[q[hh]]);
        }
        puts("");
    }
    // 最大值窗口
    {
        int hh = 0, tt = -1;
        for (int i = 1; i <= n; i ++ )
        {
            while (hh <= tt && w[q[tt]] <= w[i]) tt -- ;
            q[ ++ tt] = i;
            if (hh <= tt && i - q[hh] + 1 > m) hh ++ ;
            if (i >= m) printf("%d ", w[q[hh]]);
        }
        puts("");
    }
    return 0;
}