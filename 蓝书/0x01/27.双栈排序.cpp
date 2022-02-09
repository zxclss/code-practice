#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

const int N = 1010, M = N * N;

int n;
int a[N], f[N]; //f[i] 为后缀 a[i...n] 的最小值
int h[N], e[M], ne[M], idx;
int color[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
bool dfs(int u, int c)
{
    color[u] = c;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int ver = e[i];
        if (!color[ver] && !dfs(ver, 3 - c)) return false;
        else if(color[ver] == c) return false;
    }
    return true;
}
int main()
{
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    f[n + 1] = n + 1;//哨兵
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for (int i = n; i >= 1; i -- ) f[i] = min(f[i + 1], a[i]);
    for (int i = 1; i <= n; i ++ )
        for (int j = i + 1; j <= n; j ++ )
            if (a[i] < a[j] && f[j + 1] < a[i])
                add(i, j), add(j, i);
    bool flag = true;
    for (int i = 1; i <= n; i ++ )
        if (!color[i] && !dfs(i, 1))
            flag = false;
    if (!flag) printf("0\n");
    else
    {
        stack<int> s1, s2;
        int now = 1;
        for (int i = 1; i <= n; i ++ )
        {
            if (color[i] == 1)
            {
                while (s1.size() && s1.top() == now)
                {
                    s1.pop();
                    printf("b ");
                    now ++ ;
                }
                if (s1.size() && s1.top() < a[i])
                {
                    while (true)
                    {
                        if (s1.size() && s1.top() == now)
                        {
                            s1.pop();
                            printf("b ");
                            now ++ ;
                        }
                        else if (s2.size() && s2.top() == now)
                        {
                            s2.pop();
                            printf("d ");
                            now ++ ;
                        }
                        else break;
                    }
                }
                s1.push(a[i]);
                printf("a ");
            }
            else
            {
                while (true)
                {
                    if (s1.size() && s1.top() == now)
                    {
                        s1.pop();
                        printf("b ");
                        now ++ ;
                    }
                    else if (s2.size() && s2.top() == now)
                    {
                        s2.pop();
                        printf("d ");
                        now ++ ;
                    }
                    else break;
                }
                s2.push(a[i]);
                printf("c ");
            }
        }
        while (true)
        {
            if (s1.size() && s1.top() == now)
            {
                s1.pop();
                printf("b ");
                now ++ ;
            }
            else if (s2.size() && s2.top() == now)
            {
                s2.pop();
                printf("d ");
                now ++ ;
            }
            else break;
        }
    }
    return 0;
}