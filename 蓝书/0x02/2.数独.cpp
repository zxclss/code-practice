#include <iostream>
#include <cstring>

#define lowbit(x) x&-x
using namespace std;

const int N = 9;

int cnt[1 << N], map[1 << N];
int row[N], col[N], cell[N / 3][N / 3];
char str[110];

void init()
{
    for (int i = 0; i < N; i ++ ) row[i] = col[i] = (1 << N) - 1;
    for (int i = 0; i < 3; i ++ )
        for (int j = 0; j < 3; j ++ )
            cell[i][j] = (1 << N) - 1;
}
void draw(int x, int y, int k, bool is_set)
{
    if (is_set) str[x * N + y] = k + '1';
    else str[x * N + y] = '.';
    int v = 1 << k;
    if (!is_set) v = -v;
    row[x] -= v;
    col[y] -= v;
    cell[x / 3][y / 3] -= v;
}
int get(int x, int y)
{
    return row[x] & col[y] & cell[x / 3][y / 3];
}
bool dfs(int u)
{
    if (!u) return true;

    int x, y, z = 10;
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            if (str[i * N + j] == '.' && z > cnt[get(i, j)])
                z = cnt[get(i, j)], x = i, y = j;
    for (int i = get(x, y); i; i -= lowbit(i))
    {
        int num = map[lowbit(i)];
        draw(x, y, num, true);
        if (dfs(u - 1)) return true;
        draw(x, y, num, false);
    }
    return false;
}
int main()
{
    for (int i = 0; i < N; i ++ ) map[1 << i] = i;
    for (int i = 0; i < 1 << N; i ++ )
        for (int j = i; j; j -= lowbit(j))
            cnt[i] ++ ;
    while (cin >> str, strcmp(str, "end"))
    {
        init();
        int s = 0;
        for (int i = 0; i < N; i ++ )
            for (int j = 0; j < N; j ++ )
                if (str[i * N + j] != '.') draw(i, j, str[i * N + j] - '1', true);
                else s ++ ;
        dfs(s);
        cout << str << endl;
    }
    return 0;
}