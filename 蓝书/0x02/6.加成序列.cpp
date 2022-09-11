#include <iostream>

using namespace std;

const int N = 110;

int n;
int x[N];

bool dfs(int dep, int max_depth)
{
    if (dep > max_depth) return x[dep - 1] == n;
    
    bool st[N] = {0};
    for (int i = dep - 1; i; i -- )
    {
        for (int j = dep - 1; j; j -- )
        {
            int s = x[i] + x[j];
            if (s > n || s <= x[dep - 1] || st[s]) continue;
            st[s] = true;
            x[dep] = s;
            if (dfs(dep + 1, max_depth)) return true;
        }
    }
    return false;
}
int main()
{
    x[1] = 1;
    while (scanf("%d", &n), n)
    {
        int max_depth = 1;
        while (!dfs(2, max_depth)) max_depth ++ ;
        for (int i = 1; i <= max_depth; i ++ )
            printf("%d ", x[i]);
        puts("");
    }
    return 0;
}