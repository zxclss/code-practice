#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int SIZE = 1000010, INF = 1e9;

struct Node
{
    int value, pos;
    int prev, next;
    bool operator < (const Node &t) const
    {
        return value < t.value;
    }
} node[SIZE];
int head, tail, tot;

void initialize()
{
    tot = 2;
    head = 1, tail = 2;
    node[head].next = tail;
    node[tail].prev = head;
}

int insert(int p, int value, int pos)
{
    int q = ++ tot;
    node[q].value = value, node[q].pos = pos;
    node[node[p].next].prev = q;
    node[q].next = node[p].next;
    node[p].next = q; node[q].prev = p;
    return q;
}

void remove(int p)
{
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}

int n;
PII a[SIZE];
int res[SIZE];

void solve()
{
    unordered_map<int, int> pos;
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i].x), a[i].y = i;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i ++ )
        pos[a[i].y] = insert(node[tail].prev, a[i].x, a[i].y);
    
    node[head].value = -INF, node[tail].value = INF;
    int midx = head;
    for (int i = 1; i <= n + 1 >> 1; i ++ ) midx = node[midx].next;
    
    for (int i = n; i; i -- )
    {
        res[i] = node[midx].value;
        Node &t = node[pos[i]];
        if (t.pos == node[midx].pos) //删掉的是中位数
        {
            if (i & 1) midx = node[midx].prev;
            else midx = node[midx].next;
        }
        else
        {
            if (i & 1 && pos[i] > midx) midx = node[midx].prev;
            else if (i & 1 ^ 1 && pos[i] < midx) midx = node[midx].next;
        }
        remove(pos[i]);
    }
    for (int i = 1; i <= n; i ++ )
    {
        if (i & 1) printf("%d ", res[i]);
        if (i % 20 == 0) puts("");
    }
    if (n % 20) puts("");
}
int main()
{
    int T; scanf("%d", &T);
    for (int i = 1; i <= T; i ++ )
    {
        int C;
        scanf("%d%d", &C, &n);
        printf("%d %d\n", C, n / 2 + 1);
        solve();
    }
    return 0;
}

