#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef pair<int, string> PIS;

int f(string state)
{
    int res = 0;
    for (int i = 0; i < 9; ++i)
    {
        if (state[i] != 'x')
        {
            int t = state[i] - '1';
            res += abs(t / 3 - i / 3) + abs(t % 3 - i % 3);
        }
    }
    return res;
}
string astar(string start, string end)
{
    char op[5] = {"udlr"};
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    unordered_map<string, int> dist;
    unordered_map<string, pair<char, string>> prev;
    priority_queue<PIS, vector<PIS>, greater<PIS>> heap;
    heap.push({f(start), start});
    
    while (!heap.empty())
    {
        PIS t = heap.top();
        heap.pop();
        
        string state = t.second;
        
        if (state == end) break;
        int x, y;
        for (int i = 0; i < 9; ++i)
        {
            if (state[i] == 'x')
            {
                x = i / 3, y = i % 3;
                break;
            }
        }
        
        for (int i = 0; i < 4; ++i)
        {
            int a = x + dx[i], b = y + dy[i];
            if (a < 0 || a >= 3 || b < 0 || b >= 3) continue;
            
            string temp = state;
            swap(temp[a * 3 + b], temp[x * 3 + y]);
            
            int d = dist[state] + 1;
            if (!dist.count(temp) || dist[temp] > d)
            {
                dist[temp] = d;
                prev[temp] = {op[i], state};
                heap.push({dist[temp] + f(temp), temp});
            }
        }
    }
    string path;
    while (start != end)
    {
        path += prev[end].first;
        end = prev[end].second;
    }
    reverse(path.begin(), path.end());
    return path;
}
int main()
{
    string start, x, seq;
    while (cin >> x)
    {
        start += x;
        if (x != "x") seq += x;
    }
    string end = "12345678x";
    int t = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = i + 1; j < 8; ++j)
            if (seq[i] < seq[j])
                ++t;
    if (t & 1) puts("unsolvable");
    else cout << astar(start, end) << endl;
    return 0;
}