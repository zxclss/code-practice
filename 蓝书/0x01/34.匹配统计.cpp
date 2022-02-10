#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 10;

int n, m, Q;
char a[N], b[N];
int f[N], ne[N];

int main()
{
    scanf("%d%d%d%s%s", &n, &m, &Q, a + 1, b + 1);
    for (int i = 2, j = 0; i <= m; i ++ )
    {
        while (j && b[i] != b[j + 1]) j = ne[j];
        if (b[i] == b[j + 1]) j ++ ;
        ne[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i ++ )
    {
        while (j && a[i] != b[j + 1]) j = ne[j];
        if (a[i] == b[j + 1]) j ++ ;
        f[j] ++ ;
    }
    for (int i = m; i; i -- ) f[ne[i]] += f[i];
    while (Q -- )
    {
        int t;
        scanf("%d", &t);
        printf("%d\n", f[t] - f[t + 1]);
    }
    return 0;
}

// #include <iostream>
// #include <algorithm>
// #include <cstring>

// using namespace std;

// typedef unsigned long long ULL;

// const int N = 2e5 + 10;
// const int P = 131;

// int n, m, Q;
// ULL ha[N], hb[N], p[N];
// char a[N], b[N];
// int cnt[N];

// ULL get_hash(ULL h[], int l, int r)
// {
//     return h[r] - h[l - 1] * p[r - l + 1];
// }
// void initialize_hash()
// {
//     p[0] = 1;
//     for (int i = 1; i <= max(n, m); i ++ )
//     {
//         p[i] = p[i - 1] * P;
//         ha[i] = ha[i - 1] * P + a[i];
//         hb[i] = hb[i - 1] * P + b[i];
//     }
// }
// int main()
// {
//     scanf("%d%d%d%s%s", &n, &m, &Q, a + 1, b + 1);
//     initialize_hash();
//     for (int i = n; i; i -- )
//     {
//         int l = 0, r = n - i + 1;
//         while (l < r)
//         {
//             int mid = (l + r + 1) >> 1;
//             ULL va = get_hash(ha, i, i + mid - 1);
//             ULL vb = get_hash(hb, 1, 1 + mid - 1);
//             if (va == vb) l = mid; else r = mid - 1;
//         }
//         cnt[r] ++ ;
//     }
//     while (Q -- )
//     {
//         int t;
//         scanf("%d", &t);
//         printf("%d\n", cnt[t]);
//     }
//     return 0;
// }
