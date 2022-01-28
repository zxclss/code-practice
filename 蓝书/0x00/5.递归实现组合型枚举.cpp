#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> chosen;

void calc(int u)
{
    if (chosen.size() > m || chosen.size() + (n - u + 1) < m) return;
    if (chosen.size() == m)
    {
        for (int i: chosen)
            printf("%d ", i);
        puts("");
        return;
    }
    chosen.push_back(u);
    calc(u + 1);
    chosen.pop_back();
    calc(u + 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    calc(1);
    return 0;
}