#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

const int SIZE = 3e5 + 10;
const int P = 131;

int n;
char str[SIZE];
ULL f[SIZE], p[SIZE];
int sa[SIZE];

void initialize()
{
    p[0] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = p[i - 1] * P;
        f[i] = f[i - 1] * P + str[i];
        sa[i] = i;
    }
}
ULL get_hash(int l, int r)
{
    return f[r] - f[l - 1] * p[r - l + 1];
}
int get_max_common_prefix(int a, int b) //二分两个子数组最长前缀
{
    int l = 0, r = min(n + 1 - a, n + 1 - b);
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (get_hash(a, a + mid - 1) == get_hash(b, b + mid - 1)) l = mid;
        else r = mid - 1;
    }
    return r;
}
bool cmp(int a, int b)  //比较后缀字符串 str[a...n] 和 str[b...n] 的大小
{
    int len = get_max_common_prefix(a, b);
    int a_val = a + len > n ? 0 : str[a + len];
    int b_val = b + len > n ? 0 : str[b + len];
    return a_val < b_val;
}
int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);

    initialize();

    sort(sa + 1, sa + n + 1, cmp);
    for (int i = 1; i <= n; i ++ ) printf("%d ", sa[i] - 1);
    puts("");
    for (int i = 1; i <= n; i ++ )
    {
        if (i == 1) printf("0 ");
        else printf("%d ", get_max_common_prefix(sa[i - 1], sa[i]));
    }
    return 0;
}