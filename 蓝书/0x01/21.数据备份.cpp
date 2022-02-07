#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<LL, int> PII;

const int N = 1e5 + 10, SIZE = N << 1;

struct Node
{
	LL value;
	int idx;
	int prev, next;
} node[SIZE];
int head, tail, tot;

void initialize()
{
	tot = 2;
	head = 1, tail = 2;
	node[head].next = tail;
	node[tail].prev = head;
}

int insert(int p, int value)
{
	int q = ++ tot;
	node[q].value = value;
	node[node[p].next].prev = q;
	node[q].next = node[p].next;
	node[p].next = q; node[q].prev = p;
	return q;
}

void remove(int p)
{
    node[p].value = -1;
	node[node[p].prev].next = node[p].next;
	node[node[p].next].prev = node[p].prev;
}


priority_queue<PII, vector<PII>, greater<PII>> heap;
LL d[N];
int n, m;

int main()
{
    initialize();
    node[head].value = node[tail].value = 1e10;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++ ) scanf("%lld", &d[i]);
    for (int i = n; i > 1; i -- )
    {
        d[i] = d[i] - d[i - 1];
        heap.push({d[i], insert(node[tail].prev, d[i])});
    }
    
    LL res = 0;
    while (m)
    {
        PII t = heap.top(); heap.pop();
        
        if (t.x != node[t.y].value) continue;
        
        res += t.x;
        LL v = -t.x;
        v += node[node[t.y].prev].value;
        v += node[node[t.y].next].value;
        heap.push({v, insert(node[t.y].next, v)});
        
        remove(node[t.y].prev);
        remove(node[t.y].next);
        remove(t.y);
        m -- ;
    }
    printf("%lld\n", res);
    return 0;
}