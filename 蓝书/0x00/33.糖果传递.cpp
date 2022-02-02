#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6 + 10;

int n;
long long m, s[N], c[N];

long long calc()
{
    long long avg = m / n;
    for (int i = 1; i <= n; i ++ ) c[i] -= avg;
    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + c[i];
    sort(s + 1, s + n + 1);
    long long res = 0;
    for (int i = 1; i <= n; i ++ ) res += abs(s[i] - s[(n + 1) / 2]);
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &c[i]), m += c[i];
    printf("%lld", calc());
    return 0;
}