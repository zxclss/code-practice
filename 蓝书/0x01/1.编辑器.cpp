#include <iostream>

using namespace std;

const int N = 1e6 + 10, INF = 1e9;

int stk_l[N], stk_r[N], tt_l = 0, tt_r = 0; //下标从 1 开始，方便前缀和统计
int s[N], f[N] = {-INF};

void update_prefix(int t)
{
    s[tt_l] = s[tt_l - 1] + t;
    f[tt_l] = max(f[tt_l - 1], s[tt_l]);
}
int main()
{
    char op[2];
    int t, Q;
    cin >> Q;
    while (Q -- )
    {
        cin >> op;
        if (*op == 'I')
        {
            cin >> t;
            stk_l[ ++ tt_l] = t;
            update_prefix(t);
        }
        else if (*op == 'D')
        {
            if (!tt_l) continue;
            tt_l -- ;
        }
        else if (*op == 'L')
        {
            if (!tt_l) continue;
            stk_r[ ++ tt_r] = stk_l[tt_l -- ];
        }
        else if (*op == 'R')
        {
            if (!tt_r) continue;
            stk_l[ ++ tt_l] = stk_r[tt_r -- ];
            update_prefix(stk_l[tt_l]);
        }
        else
        {
            cin >> t;
            cout << f[t] << endl;
        }
    }
    return 0;
}