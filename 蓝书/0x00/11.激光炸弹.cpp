#include <iostream>

using namespace std;

const int N = 5010;

int n, m, res;
int s[N][N];

int main()
{
    cin >> n >> m; m = min(m, N - 1);
    for (int i = 0; i < n; i ++ )
    {
        int x, y, w;
        cin >> x >> y >> w;
        s[ ++ x][ ++ y] += w;
    }
    for (int i = 1; i < N; i ++ )
        for (int j = 1; j < N; j ++ )
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    for (int i = m; i < N; i ++ )
        for (int j = m; j < N; j ++ )
            res = max(res, s[i][j] - s[i - m][j] - s[i][j - m] + s[i - m][j - m]);
    cout << res << endl;
    return 0;
}