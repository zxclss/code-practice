#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e4 + 10, SIZE = N * 10;

int T, n;
char s[N];

struct Trie
{
    int trie[SIZE][10], tot;
    int end[SIZE];
    void initialize()
    {
        tot = 0;
        memset(end, 0, sizeof(end));
        memset(trie, 0, sizeof(trie));
    }
    bool insert(char *s)
    {
        int p = 0;
        bool has_new = true, has_found = false;
        for (int i = 0; s[i]; i ++ )
        {
            int ch = s[i] - '0';
            if (!trie[p][ch]) trie[p][ch] = ++ tot, has_new = true;
            else has_new = false;
            p = trie[p][ch];
            if (end[p]) has_found = true;
        }
        end[p] ++ ;
        return !has_found && has_new;
    }
} trie;

int main()
{
    scanf("%d", &T);
    while (T -- )
    {
        trie.initialize();
        scanf("%d", &n);
        bool flag = true;
        for (int i = 1; i <= n; i ++ )
        {
            scanf("%s", s);
            flag &= trie.insert(s);
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}