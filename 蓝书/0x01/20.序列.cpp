#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 2010;

int T, n, m;
int a[N], b[N], tmp[N];

struct Node
{
    int i, j;
    bool operator > (const Node &t) const
    {
        return a[i] + b[j] > a[t.i] + b[t.j];
    }
};

void merge_array()
{
    priority_queue<Node, vector<Node>, greater<Node>> heap;
    for (int i = 1; i <= n; i ++ ) heap.push({1, i});
    for (int i = 1; i <= n; i ++ )
    {
        Node t = heap.top();
        heap.pop();
        tmp[i] = a[t.i] + b[t.j];
        heap.push({t.i + 1, t.j});
    }
    memcpy(a, tmp, sizeof tmp);
}
void solve()
{
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    while ( -- m)
    {
        for (int i = 1; i <= n; i ++ ) scanf("%d", &b[i]);
        sort(b + 1, b + n + 1);
        merge_array();
    }
    for (int i = 1; i <= n; i ++ ) printf("%d ", a[i]);
    puts("");
}
int main()
{
    scanf("%d", &T);
    while (T -- ) solve();
    return 0;
}