#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e6 + 10;

char a[N], b[N], t[N];

void get_min(char *s)
{
    int n = strlen(s);
    for (int i = n; i < n << 1; i ++ ) s[i] = s[i % n];
    
    int i = 0, j = 1, k;
    while (i < n && j < n)
    {
        for (k = 0; k < n && s[i + k] == s[j + k]; k ++ );
        if (k == n) break;
        if (s[i + k] > s[j + k])
        {
            i = i + k + 1;
            if (i == j) i ++ ;
        }
        else
        {
            j = j + k + 1;
            if (i == j) j ++ ;
        }
    }
    
    int start = min(i, j);
    for (int c = 0; c < n; c ++ ) s[c] = s[start + c];
    s[n] = '\0';
}
int main()
{
    scanf("%s%s", a, b);
    get_min(a), get_min(b);
    if (strcmp(a, b)) puts("No");
    else
    {
        puts("Yes");
        printf("%s\n", a);
    }
    return 0;
}