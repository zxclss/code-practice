#include <iostream>
#include <queue>

using namespace std;

const int N = 1e6 + 10, M = 1010;
int n;
int id[N];

void solve()
{
    for (int i = 1, m, x; i <= n; i ++ )
    {
        cin >> m;
        for (int j = 1; j <= m; j ++ )
        {
            cin >> x;
            id[x] = i;
        }
    }
    queue<int> group[M], groups;
    string op;
    while (cin >> op, op != "STOP")
    {
        if (op == "ENQUEUE")
        {
            int t; cin >> t;
            if (!group[id[t]].size()) groups.push(id[t]);
            group[id[t]].push(t);
        }
        else
        {
            int t = groups.front();
            cout << group[t].front() << endl;
            group[t].pop();
            if (!group[t].size()) groups.pop();
        }
    }
    cout << endl;
}
int main()
{
    int T = 1;
    while (cin >> n, n)
    {
        cout << "Scenario #" << T ++  << endl;
        solve();
    }
    return 0;
}