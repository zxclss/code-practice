#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
const int SIZE = N * 31;

int n;
struct Trie
{
    int trie[SIZE][2], tot;
    void insert(int num)
    {
        int p = 0;
        for (int i = 30; i >= 0; i -- )
        {
            int ch = num >> i & 1;
            if (trie[p][ch] == 0) trie[p][ch] = ++ tot;
            p = trie[p][ch];
        }
    }
    int query(int num)
    {
        int res = 0, p = 0;
        for (int i = 30; i >= 0; i -- )
        {
            int ch = num >> i & 1;
            if (trie[p][!ch] == 0) p = trie[p][ch];
            else
            {
                res += 1 << i;
                p = trie[p][!ch];
            }
        }
        return res;
    }
}trie;

int main()
{
    scanf("%d", &n);
    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int num;
        scanf("%d", &num);
        res = max(res, trie.query(num));
        trie.insert(num);
    }
    printf("%d\n", res);
    return 0;
}