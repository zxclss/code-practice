#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 25, INF = 1e9;

int n, m;
int H[N], R[N], S = INF;
int minv[N], mins[N];

void init()
{
    R[m + 1] = H[m + 1] = INF;
    for (int i = 1; i <= m; i ++ )
    {
        mins[i] = mins[i - 1] + 2 * i * i;
        minv[i] = minv[i - 1] + i * i * i;
    }
}
void dfs(int dep, int s, int v)
{
    if (v + minv[dep] > n) return;  //(3)
    if (s + mins[dep] > S)  return; //(4)
    if (s + 2 * (n - v) / R[dep + 1] >= S) return;  //(5)
    if (!dep)
    {
        if (v == n) S = min(S, s);
        return;
    }
    for (int r = min(R[dep + 1] - 1, (int)sqrt(n - v)); r >= dep; r -- ) //(1)&(2)
    {
        for (int h = min(H[dep + 1] - 1, (n - v) / r / r); h >= dep; h -- ) //(1)&(2)
        {
            int tempS = s + 2 * r * h + (dep == m ? r * r : 0);
            int tempV = v + r * r * h;
            R[dep] = r;
            H[dep] = h;
            dfs(dep - 1, tempS, tempV);
        }
    }
}
int main()
{
    cin >> n >> m;
    init();
    dfs(m, 0, 0);
    cout << (S == INF ? 0 : S) << endl;
    return 0;
}