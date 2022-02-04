#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define x first
#define y second

typedef pair<int, int> PII;

const int N = 2e5 + 10, INF = 1e9;

int n;
PII a[N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i].x), a[i].y = i;
    sort(a + 1, a + n + 1);

    int res = 1;
    int last = n + 1, k = -1;
    for (int i = 1; i <= n; )
    {
        int j = i;
        while (j <= n && a[j].x == a[i].x) j ++ ;
        int max_idx = a[j - 1].y, min_idx = a[i].y;
        if (~k)  //上升
        {
            if (last < min_idx) last = max_idx;
            else last = min_idx, k = -1, res ++ ;
        }
        else    //下降
        {
            if (last > max_idx) last = min_idx;
            else last = max_idx, k = 1;
        }
        i = j;
    }
    cout << res << endl;
    return 0;
}