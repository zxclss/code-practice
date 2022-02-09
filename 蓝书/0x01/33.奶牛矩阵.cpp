#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100, M = 10010;

int n, m;
char row[M][N];
char col[N][M];
int ne[M];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%s", row[i] + 1);
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            col[j][i] = row[i][j];
    for (int i = 2, j = 0; i <= n; i ++ )
    {
        while (j && strcmp(row[i] + 1, row[j + 1] + 1)) j = ne[j];
        if (!strcmp(row[i] + 1, row[j + 1] + 1)) j ++ ;
        ne[i] = j;
    }
    int x = n - ne[n];
    
    for (int i = 2, j = 0; i <= m; i ++ )
    {
        while (j && strcmp(col[i] + 1, col[j + 1] + 1)) j = ne[j];
        if (!strcmp(col[i] + 1, col[j + 1] + 1)) j ++ ;
        ne[i] = j;
    }
    int y = m - ne[m];
    printf("%d\n", x * y);
    return 0;
}