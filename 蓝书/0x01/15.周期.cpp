#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int SIZE = 1e6 + 10;

int n;
char str[SIZE];
int ne[SIZE];

void solve()
{
    scanf("%s", str + 1);
    for (int i = 2, j = 0; i <= n; i ++ )
    {
        while (j && str[i] != str[j + 1]) j = ne[j];
        if (str[i] == str[j + 1]) j ++ ;
        ne[i] = j;
    }
    for (int i = 2; i <= n; i ++ )
        if (i % (i - ne[i]) == 0 && i / (i - ne[i]) > 1)
            printf("%d %d\n", i, i / (i - ne[i]));
    puts("");
}
int main()
{
    int T = 1;
    while (scanf("%d", &n), n)
    {
        printf("Test case #%d\n", T ++ );
        solve();
    }
    return 0;
}