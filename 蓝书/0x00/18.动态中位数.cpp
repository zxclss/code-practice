#include <iostream>
#include <queue>

using namespace std;

int t, n;

void adjust(priority_queue<int> &up, priority_queue<int, vector<int>, greater<int>> &dw)
{
    if (up.size() > dw.size())
    {
        dw.push(up.top());
        up.pop();
    }
    else if (dw.size() > up.size() + 1)
    {
        up.push(dw.top());
        dw.pop();
    }
}
void solve()
{
    priority_queue<int> up;
    priority_queue<int, vector<int>, greater<int>> dw;
    int cnt = 0;
    for (int i = 1; i <= n; i ++ )
    {
        cin >> t;
        if (up.size() && up.top() > t) up.push(t);
        else dw.push(t);
        
        adjust(up, dw);
        
        if (i & 1)
        {
            cout << dw.top() << " ";
            if ( ++ cnt % 10 == 0) cout << endl;
        }
    }
    if (cnt % 10) cout << endl;
}
int main()
{
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i ++ )
    {
        cin >> t >> n;
        cout << t << " " << (n + 1) / 2 << endl;
        solve();
    }
    return 0;
}