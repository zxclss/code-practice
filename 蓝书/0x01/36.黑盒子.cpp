#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 30010;
int n, m;
int a[N], b[N];
priority_queue<int, vector<int>, greater<int>> up;
priority_queue<int> dw;

void adjust(int n, int t)
{
    if (dw.size() > t)
    {
        up.push(dw.top());
        dw.pop();
    }
    else if (up.size() > n - t)
    {
        dw.push(up.top());
        up.pop();
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for (int i = 1; i <= m; i ++ ) scanf("%d", &b[i]);

    int t = 1;
    for (int i = 1, j = 1; i <= n; i ++ )
    {
        dw.push(a[i]);
        adjust(i, t);
        while (b[j] == i)
        {
            printf("%d\n", dw.top());
            j ++ , ++ t;
            adjust(i, t);
        }
    }
    return 0;
}