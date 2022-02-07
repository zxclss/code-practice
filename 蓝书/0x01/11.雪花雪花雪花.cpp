#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e5 + 10;

int n;
vector<int> snows[N];

void get_min(vector<int> &a)    //求字符串最小表示法
{
    vector<int> b(12);
    for (int i = 0; i < 12; i ++ ) b[i] = a[i % 6];
    int i = 0, j = 1, k;
    while (i < 6 && j < 6)
    {
        for (k = 0; k < 6 && b[i + k] == b[j + k]; k ++ );
        if (k == 6) break;

        if (b[i + k] > b[j + k])
        {
            i += k + 1;
            if (i == j) i ++ ;
        }
        else
        {
            j += k + 1;
            if (i == j) j ++ ;
        }
    }

    k = min(i, j);
    for (int i = 0; i < 6; i ++ ) a[i] = b[i + k];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        vector<int> snow(6), isnow(6);
        for (int j = 0; j < 6; j ++ )
            scanf("%d", &snow[j]), isnow[5 - j] = snow[j];
        get_min(snow);
        get_min(isnow);
        snows[i] = min(snow, isnow);
    }
    sort(snows + 1, snows + n + 1);

    bool flag = false;
    for (int i = 1; i < n; i ++ )
        if (snows[i] == snows[i + 1])
            flag = true;
    puts(flag ? "Twin snowflakes found." : "No two snowflakes are alike.");
    return 0;
}