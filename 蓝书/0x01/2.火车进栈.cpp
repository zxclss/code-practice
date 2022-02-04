#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int N = 25;

int n, cnt = 20;
vector<int> path;
stack<int> stk;

void dfs(int u)
{
    if (!cnt) return;
    if (path.size() == n)
    {
        for (auto &it: path) cout << it;
        cout << endl;
        cnt -- ;
        return;
    }
    if (stk.size())
    {
        path.push_back(stk.top());
        stk.pop();
        dfs(u);
        stk.push(path.back());
        path.pop_back();
    }
    if (u <= n)
    {
        stk.push(u);
        dfs(u + 1);
        stk.pop();
    }
}
int main()
{
    cin >> n;
    dfs(1);
    return 0;
}