#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef unsigned long long ULL;

const int N = 1010;
const int P = 131;

int T, n, m, a, b;
ULL h[N][N], p[N * N];
char str[N][N];
unordered_set<ULL> S;

ULL get_hash(ULL h[], int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}
void initialize_hash()
{
    p[0] = 1;
    for (int i = 1; i <= n * m; i ++ ) p[i] = p[i - 1] * P;
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            h[i][j] = h[i][j - 1] * P + str[i][j];
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (int i = 1; i <= n; i ++ ) scanf("%s", str[i] + 1);
    initialize_hash();
    for (int j = b; j <= m; j ++ )
    {
        ULL value = 0;
        int l = j - b + 1, r = j;
        for (int i = 1; i <= n; i ++ )
        {
            value = value * p[b] + get_hash(h[i], l, r);
            if (i > a) value = value - get_hash(h[i - a],l, r) * p[b * a];
            if (i >= a) S.insert(value);
        }
    }
    scanf("%d", &T);
    while (T -- )
    {
        ULL value = 0;
        for (int i = 1; i <= a; i ++ )
        {
            scanf("%s", str[i] + 1);
            for (int j = 1; j <= b; j ++ ) value = value * P + str[i][j];
        }
        puts(S.count(value) ? "1" : "0");
    }
    return 0;
}