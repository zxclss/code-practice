#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <deque>

using namespace std;

const int N = 15;

int n = 13;
deque<int> cards[N];
unordered_map<char, int> mp = {{'A', 1}, {'0', 10}, {'J', 11}, {'Q', 12}};
int cnt[N];

void dfs(int t)
{
    if (!t) return;
    cnt[t] ++ ;
    int ne = cards[t].back(); cards[t].pop_back();
    dfs(ne);
}
int main()
{
    for (int i = 2; i < 10; i ++ ) mp['0' + i] = i;
    for (int i = 1; i <= 12; i ++ )
    {
        for (int j = 0; j < 4; j ++ )
        {
            char c; cin >> c;
            cards[i].push_back(mp[c]);
        }
    }
    for (int i = 0; i < 4; i ++ )
    {
        char c; cin >> c;
        dfs(mp[c]);
    }
    int res = 0;
    for (int i = 1; i < n; i ++ )
        if (cnt[i] == 4) res ++ ;
    cout << res << endl;
    return 0;
}
