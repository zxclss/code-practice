#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 70;

int n, len, cnt, sum;
int a[N], st[N];

bool dfs(int stick, int cur, int last)
{
    if (stick == cnt) return true;
    if (cur == len) return dfs(stick + 1, 0, 0);
    
    for (int i = last + 1; i <= n; i ++ )
    {
        if (st[i]) continue;
        if (cur + a[i] > len) continue;
        
        st[i] = true;
        if (dfs(stick, cur + a[i], i)) return true;
        st[i] = false;
        
        if (!cur) return false;                 //(3)
        if (cur + a[i] == len) return false;    //(4)

        int j = i;                              //(2)
        while (j <= n && a[i] == a[j]) j ++ ;
        i = j - 1;
    }
    return false;
}
int main()
{
    while (cin >> n, n)
    {
        sum = len = cnt = 0;
        for (int i = 1; i <= n; i ++ )
        {
            cin >> a[i];
            st[i] = 0;
            sum += a[i];
            len = max(len, a[i]);
        }
        sort(a + 1, a + n + 1); //(1)
        reverse(a + 1, a + n + 1);
        while (true)
        {
            if (sum % len == 0)
            {
                cnt = sum / len;
                if (dfs(0, 0, 0)) break;
            }
            len ++ ;
        }
        printf("%d\n", len);
    }
}