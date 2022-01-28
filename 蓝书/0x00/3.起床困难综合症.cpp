#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int one = (1 << 30) - 1, non = 0;
    for (int i = 1; i <= n; i++ )
    {
        string op; int t; cin >> op >> t;
        if (op == "AND") one &= t, non &= t;
        else if (op == "XOR") one ^= t, non ^= t;
        else one |= t, non |= t;
    }
    int res = 0;
    for (int i = 30; i >= 0; i -- )
    {
        if (non >> i & 1) res += 1 << i;
        else if (one >> i & 1 && m >= 1 << i)
        {
            m -= 1 << i;
            res += 1 << i;
        }
    }
    cout << res << endl;
    return 0;
}