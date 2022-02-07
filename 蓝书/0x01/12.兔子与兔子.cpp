#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

const int SIZE = 1000010;
const int P = 13331;

int n, m;
char str[SIZE];
ULL f[SIZE], p[SIZE];

ULL get_hash(int l, int r)
{
    return f[r] - f[l - 1] * p[r - l + 1];
}
void initialize()
{
    p[0] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = p[i - 1] * P;
        f[i] = f[i - 1] * P + str[i];
    }
}
int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);
    initialize();
    scanf("%d", &m);
    while (m -- )
    {
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        puts(get_hash(l1, r1) == get_hash(l2, r2) ? "Yes" : "No");
    }
    return 0;
}