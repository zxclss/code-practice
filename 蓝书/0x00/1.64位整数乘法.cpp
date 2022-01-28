#include <iostream>

using namespace std;

// 龟速乘
long long mul(long long a, long long b, long long p)
{
    long long res = 0;
    for (; b; b >>= 1)
    {
        if (b & 1) res = (res + a) % p;
        a = a * 2 % p;
    }
    return res;
}

// 利用公式：a * b mod p = a * b - a * b / p * p
long long mul1(long long a, long long b, long long p)
{
    a %= p, b %= p;
    long long c = (long double) a * b / p;
    long long ans = a * b - c * p;
    return (ans % p + p) % p;
}

int main()
{
    long long a, b, p;
    cin >> a >> b >> p;
    cout << mul(a, b, p) << endl;
    return 0;
}