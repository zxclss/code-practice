#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 1e5 + 10;

unordered_map<char, char> mp = 
{
    {')', '('},
    {']', '['},
    {'}', '{'},
};
int n, stk[N], tt;
char str[N];

int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);

    for (int i = 1; i <= n; i ++ )
    {
        if (tt && str[stk[tt]] == mp[str[i]]) tt -- ;
        else stk[ ++ tt] = i;
    }
    
    int res = 0;
    stk[ ++ tt] = n + 1;
    for (int i = 1, last = 0; i <= tt; i ++ )
    {
        res = max(res, stk[i] - last - 1);
        last = stk[i];
    }
    printf("%d\n", res);
    return 0;
}