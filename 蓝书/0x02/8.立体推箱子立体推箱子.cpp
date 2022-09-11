#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 510;

struct Node
{
    int x, y, st;   //0立，1横，2竖
    bool operator == (const Node& t) const
    {
        return x == t.x && y == t.y && st == t.st;
    }
};

int n, m;
char g[N][N];
int d[N][N][3];

const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
Node st, ed;
bool valid(int x, int y)    //边界判断
{
    return x && x <= n && y && y <= m;
}
bool valid(Node t)    //障碍判断
{
    if (!valid(t.x, t.y)) return false;
    if (g[t.x][t.y] == '#') return false;
    if (t.st == 0 && g[t.x][t.y] == 'E') return false;
    if (t.st == 1 && g[t.x][t.y - 1] == '#') return false;
    if (t.st == 2 && g[t.x - 1][t.y] == '#') return false;
    return true;
}
void init()
{
    for (int i = 1; i <= n; i ++ ) for (int j = 1; j <= m; j ++ )
    {
        if (g[i][j] == 'O') ed = {i, j}, g[i][j] = '.';
        else if (g[i][j] == 'X')
        {
            st = {i, j, 0};
            g[i][j] = '.';
            for (int k = 0; k < 4; k ++ )
            {
                int x = i + dx[k], y = j + dy[k];
                if (valid(x, y) && g[x][y] == 'X')
                {
                    st = {x, y};
                    if (k & 1) st.st = 2;
                    else st.st = 1;
                    g[x][y] = '.';
                }
            }
        }
    }
}

const int nx[3][4] = {{0, 2, 0, -1}, {0, 1, 0, -1}, {0, 1, 0, -2}};
const int ny[3][4] = {{2, 0, -1, 0}, {1, 0, -2, 0}, {1, 0, -1, 0}};
const int ns[3][4] = {{1, 2, 1, 2}, {0, 1, 0, 1}, {2, 0, 2, 0}};

int bfs()
{
    memset(d, -1, sizeof(d));
    d[st.x][st.y][st.st] = 0;
    
    queue<Node> q;
    q.push(st);
    
    while (q.size())
    {
        Node top = q.front(); q.pop();
        for (int i = 0; i < 4; i ++ )
        {
            Node next = 
            {
                top.x + nx[top.st][i],
                top.y + ny[top.st][i],
                ns[top.st][i]
            };
            if (!valid(next)) continue;
            if (~d[next.x][next.y][next.st]) continue;
            d[next.x][next.y][next.st] = d[top.x][top.y][top.st] + 1;
            if (next == ed) return d[next.x][next.y][next.st];
            q.push(next);
        }
    }
    return -1;
}
int main()
{
    while (scanf("%d%d", &n, &m), n || m)
    {
        for (int i = 1; i <= n; i ++ ) scanf("%s", g[i] + 1);
        init();
        int res = bfs();
        if (~res) printf("%d\n", res);
        else puts("Impossible");
    }
    return 0;
}
