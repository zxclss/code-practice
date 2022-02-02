#include <iostream>

using namespace std;

const int N = 1010;

int n, root;
int p[N], fa[N], siz[N], d[N], w[N];
double v[N];

int find(int u) //边权并查集
{
    if (p[u] != u)
    {
        int t = find(p[u]);
        d[u] += d[p[u]];
        p[u] = t;
    }
    return p[u];
}
void merge(int a, int b) // 注意顺序，要求是b作为父节点，a归到b下面，和一般并查集不一样
{
    p[a] = b;
    d[a] += siz[b];
    siz[b] += siz[a];
}
int get_maxid()
{
    double maxv = 0;
    int id = -1;
    for (int i = 1; i <= n; i ++ )
    {
        if (i != root && find(i) == i && v[i] > maxv)
        {
            id = i;
            maxv = v[i];
        }
    }
    return id;
}

int main()
{
    //读入和初始化
    cin >> n >> root;
    for (int i = 1; i <= n; i ++ )
        cin >> w[i], v[i] = w[i], d[i] = 0, p[i] = i, siz[i] = 1;
    
    for (int i = 1, a, b; i < n; i ++ )
        cin >> a >> b, fa[b] = a;
    
    for (int i = 1; i < n; i ++ )
    {
        int t = get_maxid(), father = find(fa[t]);
        v[father] = (v[t] * siz[t] + v[father] * siz[father]) / (siz[t] + siz[father]);;
        merge(t, father);
    }
    int res = 0;
    for (int i = 1; i <= n; i ++ )
        res += (d[i] + 1) * w[i];
    cout << res << endl;
    return 0;
}