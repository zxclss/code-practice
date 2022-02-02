#include <iostream>
#include <cstring>

using namespace std;

const int N = 2200;
char g[N][N];

void dfs(int x, int y, int k)
{
    if (k == 1)
    {
        g[x][y] = 'X';
        return;
    }
    k /= 3;
    dfs(x, y, k);
    dfs(x, y + 2 * k, k);
    dfs(x + k, y + k, k);
    dfs(x + 2 * k, y, k);
    dfs(x + 2 * k, y + 2 * k, k);
}
int main()
{
    int n;
    while (cin >> n, ~n)
    {
        memset(g, 0, sizeof g);
        int k = 1;
        for (int i = 0; i < n - 1; i ++ ) k *= 3;
        dfs(0, 0, k);
        for (int i = 0; i < k; i ++ )
        {
            for (int j = 0; j < k; j ++ )
                if (g[i][j]) cout << g[i][j];
                else cout << " ";
            cout << endl;
        }
        cout << "-" << endl;
    }
    return 0;
}