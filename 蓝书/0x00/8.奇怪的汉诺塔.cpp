#include <iostream>
#include <cstring>

using namespace std;

int f[15], d[15];
int main()
{
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int n = 1; n <= 12; n ++ )
    {
        d[n] = 2 * d[n - 1] + 1;
        for (int i = 0; i < n; i ++ )
            f[n] = min(f[n], 2 * f[i] + d[n - i]);
        cout << f[n] << endl;
    }
    return 0;
}