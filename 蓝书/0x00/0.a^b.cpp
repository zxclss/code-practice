#include <iostream>

using namespace std;

int power(int a, int b, int p)
{
    int res = 1 % p;
    for (; b; b >>= 1)
    {
        if (b & 1) res = (long long) res * a % p;
        a = (long long) a * a % p;
    }
    return res;
}
int main()
{
    int a, b, p;
    cin >> a >> b >> p;
    cout << power(a, b, p) << endl;
    return 0;
}