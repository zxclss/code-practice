#include <iostream>
#include <queue>

using namespace std;

int n;
priority_queue<int, vector<int>, greater<int>> heap;

int main()
{
    scanf("%d", &n);
    for (int i = 1, t; i <= n; i ++ ) scanf("%d", &t), heap.push(t);
    int res = 0;
    while (heap.size() > 1)
    {
        int a = heap.top(); heap.pop();
        int b = heap.top(); heap.pop();
        res += a + b;
        heap.push(a + b);
    }
    printf("%d\n", res);
    return 0;
}