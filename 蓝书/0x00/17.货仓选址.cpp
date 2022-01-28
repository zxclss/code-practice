#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++ ) cin >> a[i];
    sort(a, a + n);
    int s = 0;
    for (int i = 0; i < n; i ++ ) s += abs(a[n / 2] - a[i]);
    cout << s << endl;
    return 0;
}