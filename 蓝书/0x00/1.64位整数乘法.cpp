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

// 64位整数乘法的long double算法
typedef unsigned long long ull;
ull mul(ull a, ull b, ull p) {
	a %= p, b %= p;  // 当a,b一定在0~p之间时，此行不必要
	ull c = (long double)a * b / p;
	ull x = a * b, y = c * p;
	long long ans = (long long)(x % p) - (long long)(y % p);
	if (ans < 0) ans += p;
	return ans;
}

int main()
{
    long long a, b, p;
    cin >> a >> b >> p;
    cout << mul(a, b, p) << endl;
    return 0;
}