#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> chosen;

void calc(int x)
{
    if (x == n + 1)
    {
        for (int i = 0; i < chosen.size(); i ++ )
            printf("%d ", chosen[i]);
        puts("");
        return;
    }
    calc(x + 1);
    chosen.push_back(x);
    
    calc(x + 1);
    chosen.pop_back();
}
int main()
{
    scanf("%d", &n);
    calc(1);
    return 0;
}