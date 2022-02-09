#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 3010;

int T;

string dfs(string &s, int &u)
{
    vector<string> sqs;
    u ++ ;
    while (s[u] == '0') sqs.push_back(dfs(s, u));
    u ++ ;

    sort(sqs.begin(), sqs.end());
    string res;
    for (auto &it: sqs) res += it;
    res = '0' + res + '1';
    return res;
}
int main()
{
    scanf("%d", &T);
    while (T -- )
    {
        string a, b;
        cin >> a >> b;
        a = '0' + a + '1', b = '0' + b + '1';
        int ua = 0, ub = 0;
        puts(dfs(a, ua) == dfs(b, ub) ? "same" : "different");
    }
    return 0;
}