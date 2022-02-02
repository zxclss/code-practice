#include <iostream>

using namespace std;

const int N = 110, INF = 1e9;

int n;
int s[N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            cin >> s[i][j], s[i][j] += s[i - 1][j];
    
    int res = -INF;
    for (int x1 = 0; x1 <= n; x1 ++ )
    {
        for (int x2 = x1 + 1; x2 <= n; x2 ++ )
        {
            int val = 0;
            for (int y = 1; y <= n; y ++ )
            {
                val = max(val, 0) + s[x2][y] - s[x1][y];
                res = max(res, val);
            }
        }
    }
    cout << res << endl;
    return 0;
}