#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 5e4 + 10;

int n;
int res[N];
struct Seg
{
    int l, r, id;
    bool operator<(const Seg& t) const
    {
        return l < t.l;
    }
}seg[N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> seg[i].l >> seg[i].r, seg[i].id = i;
    sort(seg + 1, seg + n + 1);
    
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    for (int i = 1; i <= n; i ++ )
    {
        if (heap.empty() || heap.top().x >= seg[i].l)
        {
            res[seg[i].id] = heap.size() + 1;
            heap.push({seg[i].r, heap.size() + 1});
        }
        else
        {
            int t = heap.top().y;
            heap.pop();
            res[seg[i].id] = t;
            heap.push({seg[i].r, t});
        }
    }
    cout << heap.size() << endl;
    for (int i = 1; i <= n; i ++ ) cout << res[i] << endl;
    return 0;
}