#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;

int get(char c)
{
    if (isdigit(c)) return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    return c - 'a' + 36;
}
char put(int v)
{
    if (v < 10) return '0' + v;
    if (v < 36) return 'A' + v - 10;
    return 'a' + v - 36;
}
int div(vector<int> &a, int b)
{
    int r = 0;
    for (int i = a.size() - 1; ~i; i -- )
    {
        r = r * n + a[i];
        a[i] = r / b;
        r %= b;
    }
    while (a.size() && a.back() == 0) a.pop_back();
    return r;
}
void solve()
{
    string line, res;
    vector<int> num;
    cin >> n >> m >> line;
    cout << n << " " << line << endl << m << " ";
    for (int i = line.size() - 1; ~i; i -- ) num.push_back(get(line[i]));
    
    while (num.size()) res.push_back(put(div(num, m)));
    
    reverse(res.begin(), res.end());
    cout << res << endl;
}
int main()
{
    int T; cin >> T;
    while (T -- )
    {
        solve();
        cout << endl;
    }
    return 0;
}