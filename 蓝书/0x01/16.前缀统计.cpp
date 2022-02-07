#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int SIZE = 1e6 + 10;

int n, m;
char str[SIZE];
struct Trie
{
    int trie[SIZE][26], tot;
    int end[SIZE];
    void insert(char *str)
    {
        int p = 0, n = strlen(str);
        for (int i = 0; i < n; i ++ )
        {
            int ch = str[i] - 'a';
            if (!trie[p][ch]) trie[p][ch] = ++ tot;
            p = trie[p][ch];
        }
        end[p] ++ ;
    }
    int query(char *str)
    {
        int res = 0;
        int p = 0, n = strlen(str);
        for (int i = 0; i < n; i ++ )
        {
            int ch = str[i] - 'a';
            if (!trie[p][ch]) return res;
            p = trie[p][ch];
            res += end[p];
        }
        return res;
    }
};
int main()
{
    Trie trie;
    scanf("%d%d", &n, &m);
    while (n -- )
    {
        scanf("%s", str);
        trie.insert(str);
    }
    while (m -- )
    {
        scanf("%s", str);
        printf("%d\n", trie.query(str));
    }
    return 0;
}