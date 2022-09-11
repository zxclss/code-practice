#include <iostream>
#include <cstring>

using namespace std;

const int N = 16;

int map[1 << N], ones[1 << N];

int state[N][N];
char str[N][N + 1];

int bkstate[N * N + 1][N][N], bk2state[N * N + 1][N][N];
char bkstr[N * N + 1][N][N + 1];


inline int lowbit(int u)
{
    return u & -u;
}
void draw(int x, int y, int t)
{
    str[x][y] = t + 'A';
    for (int i = 0; i < N; i ++ )
    {
        state[i][y] &= ~(1 << t);
        state[x][i] &= ~(1 << t);
    }
    int sx = x / 4 * 4, sy = y / 4 * 4;
    for (int i = 0; i < N / 4; i ++ )
        for (int j = 0; j < N / 4; j ++ )
            state[sx + i][sy + j] &= ~(1 << t);
    state[x][y] = 1 << t;
}
bool remove(int cnt)
{
    memcpy(str, bkstr[cnt], sizeof(str));
    memcpy(state, bkstate[cnt], sizeof(state));
    return false;
}
bool dfs(int cnt)
{
    if (!cnt) return true;

    int kcnt = cnt;
    memcpy(bkstr[kcnt], str, sizeof(str));
    memcpy(bkstate[kcnt], state, sizeof(state));

    //(1.1) & (1.2)
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            if (str[i][j] == '-' && ones[state[i][j]] == 1) //sole choice
                draw(i, j, map[state[i][j]]), cnt -- ;
            else if (!state[i][j]) return remove(kcnt); //no choice
    //(2)
    for (int i = 0; i < N; i ++ )   //deal row
    {
        int dir_alpha = 0, sole_alpha = (1 << N) - 1;
        int drawn = 0;
        for (int j = 0; j < N; j ++ )
        {
            int s = state[i][j];
            sole_alpha &= ~(dir_alpha & s);
            dir_alpha |= s;
            if (str[i][j] != '-') drawn |= s;
        }
        if (dir_alpha != (1 << N) - 1) return remove(kcnt);
        for (int j = sole_alpha; j; j -= lowbit(j))
        {
            int t = lowbit(j);
            if (drawn & t) continue;
            for (int k = 0; k < N; k ++ )
                if (state[i][k] & t)
                    draw(i, k, map[t]), cnt -- ;
        }
    }
    //(3)
    for (int i = 0; i < N; i ++ )   //deal column
    {
        int dir_alpha = 0, sole_alpha = (1 << N) - 1;
        int drawn = 0;
        for (int j = 0; j < N; j ++ )
        {
            int s = state[j][i];
            sole_alpha &= ~(dir_alpha & s);
            dir_alpha |= s;
            if (str[j][i] != '-') drawn |= s;
        }
        if (dir_alpha != (1 << N) - 1) return remove(kcnt);
        for (int j = sole_alpha; j; j -= lowbit(j))
        {
            int t = lowbit(j);
            if (drawn & t) continue;
            for (int k = 0; k < N; k ++ )
                if (state[k][i] & t)
                    draw(k, i, map[t]), cnt -- ;
        }
    }
    //(4)
    for (int i = 0; i < N; i ++ )
    {
        int dir_alpha = 0, sole_alpha = (1 << N) - 1;
        int drawn = 0;
        for (int j = 0; j < N; j ++ )
        {
            int sx = i / 4 * 4, sy = i % 4 * 4;
            int dx = j / 4, dy = j % 4;
            int s = state[sx + dx][sy + dy];
            sole_alpha &= ~(dir_alpha & s);
            dir_alpha |= s;
            if (str[sx + dx][sy + dy] != '-') drawn |= s;
        }
        if (dir_alpha != (1 << N) - 1) return remove(kcnt);
        for (int j = sole_alpha; j; j -= lowbit(j))
        {
            int t = lowbit(j);
            if (drawn & t) continue;
            for (int k = 0; k < N; k ++ )
            {
                int sx = i / 4 * 4, sy = i % 4 * 4;
                int dx = k / 4, dy = k % 4;
                if (state[sx + dx][sy + dy] & t)
                    draw(sx + dx, sy + dy, map[t]), cnt -- ;
            }
        }
    }

    if (!cnt) return true;
    int s = 100, x, y;
    for (int i = 0; i < N; i ++ )
        for (int j = 0; j < N; j ++ )
            if (str[i][j] == '-' && ones[state[i][j]] < s)
                s = ones[state[i][j]], x = i, y = j;
    memcpy(bk2state[kcnt], state, sizeof(state));
    for (int i = state[x][y]; i; i -= lowbit(i))
    {
        memcpy(state, bk2state[kcnt], sizeof(state));
        int t = map[lowbit(i)];
        draw(x, y, t);
        if (dfs(cnt - 1)) return true;
    }
    memcpy(str, bkstr[kcnt], sizeof(str));
    memcpy(state, bkstate[kcnt], sizeof(state));
    return false;
}
int main()
{
    for (int i = 0; i < N; i ++ ) map[1 << i] = i;
    for (int i = 0; i < 1 << N; i ++ )
        for (int j = i; j; j -= lowbit(j))
            ones[i] ++ ;
    while (cin >> str[0])
    {
        for (int i = 1; i < N; i ++ ) cin >> str[i];
        for (int i = 0; i < N; i ++ )
            for (int j = 0; j < N; j ++ )
                state[i][j] = (1 << N) - 1;
        int cnt = 0;
        for (int i = 0; i < N; i ++ )
            for (int j = 0; j < N; j ++ )
                if (str[i][j] != '-')
                    draw(i, j, str[i][j] - 'A');
                else cnt ++ ;
        dfs(cnt);
        for (int i = 0; i < N; i ++ ) cout << str[i] << endl;
        cout << endl;
    }
    return 0;
}