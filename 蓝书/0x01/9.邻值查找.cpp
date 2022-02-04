#include <iostream>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int SIZE = 1e5 + 10;

int n;
struct Node
{
    int val, pos;
    int l, r;
    bool operator< (const Node &t) const
    {
        return val < t.val;
    }
} node[SIZE];
int head, tail;
int pos[SIZE];
PII res[SIZE];


int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &node[i].val), node[i].pos = i;
    sort(node + 1, node + n + 1);
    
    head = 0, tail = n + 1, node[head].r = 1, node[tail].l = n;
    for (int i = 1; i <= n; i ++ )
    {
        pos[node[i].pos] = i;
        node[i].l = i - 1;
        node[i].r = i + 1;
    }
    
    for (int i = n; i > 1; i -- )
    {
        int s = 2e9, id = -1;
        auto &t = node[pos[i]];
        if (t.l != head && s > abs(t.val - node[t.l].val))
        {
            s = abs(t.val - node[t.l].val);
            id = node[t.l].pos;
        }
        if (t.r != tail && s > abs(t.val - node[t.r].val))
        {
            s = abs(t.val - node[t.r].val);
            id = node[t.r].pos;
        }
        res[i] = {s, id};
        node[t.l].r = t.r;
        node[t.r].l = t.l;
    }
    for (int i = 2; i <= n; i ++ ) printf("%d %d\n", res[i].x, res[i].y);
    return 0;
}