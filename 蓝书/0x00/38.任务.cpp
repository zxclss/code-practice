#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
PII mach[N], task[N];

int main()
{
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i ++ ) cin >> mach[i].x >> mach[i].y;
        for (int i = 1; i <= m; i ++ ) cin >> task[i].x >> task[i].y;
        sort(mach + 1, mach + n + 1);
        sort(task + 1, task + m + 1);
        
        long long res = 0;
        int cnt = 0;
        multiset<int> level;
        for (int i = m, j = n; i; i -- )
        {
            while (j && mach[j].x >= task[i].x) level.insert(mach[j -- ].y);
            auto it = level.lower_bound(task[i].y);
            if (it != level.end())
            {
                cnt ++ ;
                res += 500 * task[i].x + 2 * task[i].y;
                level.erase(it);
            }
        }
        cout << cnt << " " << res << endl;
    }
    return 0;
}