#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = N << 1, SIZE = N *31;

int n;
int head[N], ver[M], edge[M], nxt[M], tot;

void add(int x, int y, int z) {
    ver[ ++ tot] = y, edge[tot] = z;
    nxt[tot] = head[x], head[x] = tot;
}
struct Trie
{
    int trie[SIZE][2], tot;
    void insert(int num)
    {
        int p = 0;
        for (int i = 30; ~i; i -- )
        {
            int ch = num >> i & 1;
            if (!trie[p][ch]) trie[p][ch] = ++ tot;
            p = trie[p][ch];
        }
    }
    int query(int num)
    {
        int res = 0, p = 0;
        for (int i = 30; ~i; i -- )
        {
            int ch = num >> i & 1;
            if (!trie[p][!ch]) p = trie[p][ch];
            else
            {
                res += 1 << i;
                p = trie[p][!ch];
            }
        }
        return res;
    }
}trie;
int dist[N];

void dfs(int u, int xor_len, int fa)
{
    dist[u] = xor_len;
    for (int i = head[u]; i; i = nxt[i])
    {
        if (ver[i] == fa) continue;
        dfs(ver[i], xor_len ^ edge[i], u);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a + 1, b + 1, c), add(b + 1, a + 1, c);
    }
    dfs(1, 0, 0);
    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int val = dist[i];
        res = max(res, trie.query(val));
        trie.insert(val);
    }
    printf("%d\n", res);
    return 0;
}