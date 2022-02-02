#include <iostream>
#include <cstring>

using namespace std;

const int N = 10, INF = 0x3f3f3f3f;

int n = 4;
char a[N][N], b[N][N];

void change(char &c)
{
    if (c == '-') c = '+';
    else c = '-';
}
void turn(int x, int y)
{
    for (int i = 0; i < n; i ++ ) change(a[x][i]);
    for (int i = 0; i < n; i ++ ) change(a[i][y]);
    change(a[x][y]);
}
int main()
{
    for (int i = 0; i < n; i ++ ) cin >> b[i];
    int res = INF, state;
    for (int op = 0; op < 1 << n * n; op ++ )
    {
        memcpy(a, b, sizeof b);
        
        int cnt = 0;
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                if (op >> i * n + j & 1)
                    turn(i, j), cnt ++ ;
        if (cnt >= res) continue;
        bool ok = true;
        for (int i = 0; i < n; i ++ )
            for (int j = 0; j < n; j ++ )
                if (a[i][j] == '+')
                    ok = false;
        if (ok) res = cnt, state = op;
    }
    cout << res << endl;
    for (int i = 0; i < n; i ++ )
        for(int j = 0; j < n; j ++ )
            if (state >> i * n + j & 1)
                cout << i + 1 << " " << j + 1 << endl;
    return 0;
}