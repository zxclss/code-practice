#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int SIZE = 10010;

int n;
struct Node
{
    int p, d;
    bool operator < (const Node &t) const
    {
        return d < t.d;
    }
} a[SIZE];

int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i ++ ) scanf("%d%d", &a[i].p, &a[i].d);
        sort(a + 1, a + n + 1);
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int i = 1; i <= n; i ++ )
        {
            heap.push(a[i].p);
            if (heap.size() > a[i].d) heap.pop();
        }
        int res = 0;
        while (heap.size())
        {
            res += heap.top();
            heap.pop();
        }
        printf("%d\n", res);
    }
    return 0;
}