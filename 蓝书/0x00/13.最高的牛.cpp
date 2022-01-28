#include <iostream>
#include <set>

using namespace std;

typedef pair<int, int> PII;

const int N = 10010;

int n, p, h, m;
int b[N];
set<PII> S;

int main()
{
    cin >> n >> p >> h >> m; b[1] = h;
    while (m -- )
    {
        int x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        
        if (S.count({x, y})) continue;
        
        S.insert({x, y});
        b[x + 1] -- , b[y] ++ ;
    }
    for (int i = 1; i <= n; i ++ )
    {
        b[i] = b[i - 1] + b[i];
        cout << b[i] << endl;
    }
    return 0;
}