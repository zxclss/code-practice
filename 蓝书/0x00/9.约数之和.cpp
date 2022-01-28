#include <iostream>

using namespace std;

const int mod = 9901;

int a, b, s = 1;

int power(int a, int b, int p = mod)
{
    int res = 1 % p;
    for (; b; b >>= 1)
    {
        if (b & 1) res = (long long) res * a % p;
        a = (long long) a * a % p;
    }
    return res;
}
int calc(int p, int c)
{
    if (!c) return 1;
    if (c & 1) return (calc(p, c / 2) * (power(p, (c + 1) / 2) % mod + 1)) % mod;
    return (power(p, c) + calc(p, c - 1)) % mod;
}
int main()
{
    cin >> a >> b;
    for (int i = 2; i <= a / i; i ++ )
    {
        if (a % i == 0)
        {
            int cnt = 0;
            while (a % i == 0) a /= i, cnt ++ ;
            s = s * calc(i, cnt * b) % mod;
        }
    }
    if (a > 1) s = s * calc(a, b) % mod;
    else if (!a) s = 0;
    cout << s << endl;
    return 0;
}