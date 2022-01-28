#include <iostream>
#include <vector>

using namespace std;

int n;
int order[20];
bool chosen[20];

void calc(int u)
{
    if (u == n + 1)
    {
        for (int i = 1; i <= n; i ++ )
            printf("%d ", order[i]);
        puts("");
        return;
    }
    for (int i = 1; i <= n; i ++ )
    {
        if (chosen[i]) continue;
        chosen[i] = true;
        order[u] = i;
        calc(u + 1);
        order[u] = 0;
        chosen[i] = false;
    }
}
int main()
{
    scanf("%d", &n);
    calc(1);
    return 0;
}