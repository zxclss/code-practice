#include <iostream>
#include <queue>
#include <algorithm>

#define x first 
#define y second

using namespace std;

typedef pair<int, int> PII;

const int SIZE = 1e5 + 10;

int n, m, a[SIZE];
priority_queue<PII, vector<PII>, greater<PII>> heap;

struct Node
{
    int value;
    bool st;
    int prev, next;
} node[SIZE];
int head, tail, tot;

void initialize()
{
    head = 1, tail = tot = 2;
    node[head].next = tail;
    node[tail].prev = head;
}
int insert(int p, int value)
{
    int q = ++ tot;
    node[q] = {value, false, p, node[p].next};
    node[node[p].next].prev = q, node[p].next = q;
    return q;
}
void remove(int p)
{
    node[p].st = true;
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}

signed main()
{
    scanf("%d%d", &n, &m);

    // 连续正负数分段（0可以被归为任意一段去）
    int k = 1;
    for (int i = 1; i <= n; i ++ )
    {
        int t; scanf("%d", &t);
        if ((long long) a[k] * t < 0) a[ ++ k] = t;
        else a[k] += t;
    }
    
    n = k;
    
    int cnt = 0, sum = 0;
    for (int i = 1; i <= n; i ++ )
        if (a[i] > 0)
            cnt ++ , sum += a[i];
    
    initialize();
    for (int i = 1; i <= n; i ++ )
    {
        int p = insert(node[tail].prev, a[i]);
        heap.push({abs(a[i]), p});
    }
    
    while (cnt > m)
    {
        while (node[heap.top().y].st) heap.pop();
        PII top = heap.top(); heap.pop();
        int val = top.x, p = top.y;
        // 不删在左右两端的负数段（不减少正数段数），但可以删左右两端正数段
        if (node[p].prev != head && node[p].next != tail || node[p].value > 0)
        {
            cnt -- ;
            sum -= val;
            
            int prev = node[p].prev, next = node[p].next;
            node[p].value += node[prev].value + node[next].value;
            
            heap.push({abs(node[p].value), p});
            if (prev != head) remove(prev);
            if (next != tail) remove(next);
        }
    }
    printf("%d\n", sum);
    
    return 0;
}