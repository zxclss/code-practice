#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int,int> PII;
const int N = 25;

struct Node
{
    int x, y, dir;
};

int n, m;
char g[N][N];
bool stman[N][N];
PII dist[N][N][4];

vector<int> path[N][N][4];
Node pre[N][N][4];

bool valid(int x, int y)
{
    return x && x <= n && y && y <= m && g[x][y] != '#';
}
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int bfs_man(PII start, PII end, PII box, vector<int> &seq)
{
    static int pre[N][N];
    memset(pre, -1, sizeof(pre));
    memset(stman, 0, sizeof(stman));
    stman[start.x][start.y] = true;
    stman[box.x][box.y] = true;
    queue<PII> q;
    q.push({start.x, start.y});
    while (q.size())
    {
        PII top = q.front(); q.pop();
        if (end == top)
        {
            for (int x = top.x, y = top.y; ~pre[x][y]; )
            {
                int d = pre[x][y];
                seq.push_back(d);
                x = x + dx[d ^ 1], y = y + dy[d ^ 1];
            }
            return seq.size();
        }
        for (int i = 0; i < 4; i ++ )
        {
            int x = top.x + dx[i], y = top.y + dy[i];
            if (valid(x, y) && !stman[x][y])
            {
                pre[x][y] = i;
                stman[x][y] = true;
                q.push({x, y});
            }
        }
    }
    return -1; 
}
bool bfs(Node& end)
{
    memset(dist, -1, sizeof(dist));
    memset(pre, -1, sizeof(pre));
    //find the people position and intialize the point
    PII stm, stb;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            if (g[i][j] == 'S') stm = {i, j}, g[i][j] = '.';
            else if (g[i][j] == 'B') stb = {i, j}, g[i][j] = '.';
    
    //insert the start point into the bfs auxiliary queue
    queue<Node> q;
    for (int i = 0; i < 4; i ++ )
    {
        int x = stb.x - dx[i], y = stb.y - dy[i];
        if (!valid(x, y)) continue;
        
        vector<int> seq;
        int cnt = bfs_man(stm, {x, y}, stb, seq);
        if (cnt != -1)
        {
            //for (auto it: seq) cout << it << " "; cout << endl;
            dist[stb.x][stb.y][i] = {0, cnt};
            path[stb.x][stb.y][i] = seq;
            q.push({stb.x, stb.y, i});
        }
    }
    
    PII res = {1e9, 1e9};
    bool flag = false;
    while (q.size())
    {
        Node top = q.front(); q.pop();
        //printf("man:%d %d box:%d %d dir:%d\n", top.x - dx[top.dir], top.y - dy[top.dir], top.x, top.y, top.dir);
        // check the end
        if (g[top.x][top.y] == 'T')
        {
            flag = true;
            if (res > dist[top.x][top.y][top.dir])
            {
                res = dist[top.x][top.y][top.dir];
                end = top;
            }
            continue;
        }

        PII man_pos = {top.x - dx[top.dir], top.y - dy[top.dir]};   //position the man locates
        //find other trans path
        for (int k = 0; k < 4; k ++ )
        {
            int bx = top.x + dx[k], by = top.y + dy[k]; //the goal of the box
            int px = top.x - dx[k], py = top.y - dy[k]; //the position man need to reach
            if (!valid(px, py) || !valid(bx, by)) continue;
            //try to push the box
            vector<int> seq;
            int cnt = bfs_man(man_pos, {px, py}, {top.x, top.y}, seq);
            if (cnt != -1)  //cal the distance
            {
                PII temp = {dist[top.x][top.y][top.dir].x + 1, dist[top.x][top.y][top.dir].y + cnt};
                if (dist[bx][by][k].x == -1)
                {
                    pre[bx][by][k] = top;
                    path[bx][by][k] = seq;
                    dist[bx][by][k] = temp;
                    q.push({bx, by, k});
                }
                else if (dist[bx][by][k] > temp)
                {
                    pre[bx][by][k] = top;
                    path[bx][by][k] = seq;
                    dist[bx][by][k] = temp;
                }
            }
        }
    }
    //cout << end.x << " " << end.y << endl;
    return flag;
}
int main()
{
    int T = 1;
    while (scanf("%d%d", &n, &m), n || m)
    {
        printf("Maze #%d\n", T ++ );
        for (int i = 1; i <= n; i ++ ) scanf("%s", g[i] + 1);
        Node end;
        if (!bfs(end)) puts("Impossible.");
        else
        {
            char ops[] = {"nswe"};
            string res;
            while (pre[end.x][end.y][end.dir].dir != -1)
            {
                //cout << end.x << " " << end.y << " " << end.dir << endl;
                res += ops[end.dir] - 32;
                for (auto dir: path[end.x][end.y][end.dir]) res += ops[dir];
                end = pre[end.x][end.y][end.dir];
            }
            if (path[end.x][end.y][end.dir].size())
                for (auto dir: path[end.x][end.y][end.dir]) res += ops[dir];
            reverse(res.begin(), res.end());
            cout << res << endl;
        }
        puts("");
    }
    return 0;
}