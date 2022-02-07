#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef unsigned long long ULL;
typedef pair<ULL, int> PII;

const int N = 1e5 + 10;

priority_queue<PII, vector<PII>, greater<PII>> heap;
int n, k;   //k - 1 | n - 1

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i ++ )
    {
        ULL t;
        scanf("%llu", &t);
        heap.push({t, 0});
    }
    for (;(n - 1) % (k - 1); n ++ ) heap.push({0, 0});
    
    ULL res = 0;
    while (heap.size() > 1)
    {
        ULL s = 0; int height = -1;
        for (int i = 1; i <= k; i ++ )
        {
            auto t = heap.top(); heap.pop();
            s += t.x;
            if (height == -1 || height < t.y) height = t.y;
        }
        res += s;
        heap.push({s, height + 1});
    }
    printf("%llu\n%d", res, heap.top().y);
    return 0;
}