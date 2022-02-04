#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 6000010, M = 120010;


LL res[N], tt;
int q[M];
bool st[M];

void multi(int b)
{
    LL t = 0;
    for (int i = 0; i <= tt; i ++ )
    {
        res[i] = res[i] * b + t;
        t = res[i] / 1000000000;
        res[i] %= 1000000000;
    }
    while (t)
    {
        res[++tt] = t % 1000000000;
        t /= 1000000000;
    }
}

void out()
{
    printf("%lld", res[tt]);
    for (int i = tt - 1; i >= 0; i -- ) printf("%09lld", res[i]);
    cout << endl;
}

int get(int n, int p)
{
    int s = 0;
    while (n) s += n / p, n /= p;
    return s;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= 2 * n; i ++ )
        for (int j = i + i; j <= 2 * n; j += i)
            st[j] = true;

    for (int i = 2; i <= n * 2; i ++ )
        if (!st[i])
        {
            q[i] = get(n * 2, i) - get(n * 2 - n, i) * 2;
        }

    int k = n + 1;
    for (int i = 2; i <= k; i ++ )
        while (k % i == 0)
        {
            k /= i;
            q[i] -- ;
        }

    res[0] = 1;

    for (int i = 2; i <= n * 2; i ++ )
        while (q[i] -- )
            multi(i);

    out();

    return 0;
}