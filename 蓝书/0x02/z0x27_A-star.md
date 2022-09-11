---
title: 《算法竞赛进阶指南》0x27 A-star
date: 2022-6-5
categories: 算法竞赛进阶指南
tag:
- 算法竞赛进阶指南
---

# A-star

在先前提到的优先队列BFS方法中，是每轮从堆中取出的 “当前代价最小” 的状态进行扩展，这样每个状态第一次从堆中取出时，就得到了从初始状态到该状态的最小代价

如果目标状态是给定的，那么这个方法存在缺陷：一个状态可能到初状的代价很小，但到目标态的代价很大；一个状态可能到初态的代价很大，但到目标态的代价很小

而对于优先队列BFS来说，他会选择前者进行更新，从而导致求出最优解的搜索量增大

为提高效率，考虑引入能够对未来可能产生的代价进行预估的方法

我们可以设计一个 “**估价函数**”，以任意状态为输入，计算出从该状态到目标状态所需代价的估值

在搜索中，仍需要建立一个堆，不断从堆中取出 “**当前代价 + 未来估价**” **最小** 的状态扩展

设计估价函数的基本准则：

- 设当前状态 `state` 到目标状态所需代价的估值为 `f(state)`
- 设在未来的搜索中，实际求出的从当前状态 `state` 到目标状态的最小代价为 `g(state)`
- 对于任意的 `state`，始终有 `f(state) <= g(state)` （估值永远不能大于未来的实际代价）

在保证估值不大于未来实际代价后，那么即使估价不太精确，导致非最优解搜索路径上的状态 `s` 先扩展到了目标状态，但随着 “当前代价” 的不断累加，在目标状态被取出之前的某一时刻：

1. 根据 `s` 并非最优，`s` 更新的目标状态的 “当前代价” 就会大于从初态到目标态的最小代价
2. 对于最优解搜索路径上的状态 `t`，因为 `f(t) <= g(t)`，所有 `t` 的 “当前代价” 加上估值必定小于等于 `t` 的 “当前代价” 加上未来实际代价，而后者的含义就是初态到目标态的最小代价

结合上述两点，可知 “`t` 的当前代价加上 `f(t)`” 小于 `s` 更新的目标状态的当前代价。因此，`t` 就会被从堆中取出进行扩展，最终更新到目标状态上，产生最优解。（并且该事件发生在目标状态被取出优先队列之前）

这种 **带有估价函数的优先队列BFS就成为A-star算法**

只要保证对于任意状态`state`，都有`f(state) <= g(state)`，A-star算法就一定能 **在目标状态第一次从堆中被取出时得到最优解**，并且 **在搜索过程中每个状态只需要被扩展一次** （之后再被取出时就可以直接忽略）

估价`f(state)`越接近`g(state)`，效率就越高；若估价为 0，则退化为优先队列BFS

# 习题

## 第 K 短路

### 题目描述

给定一张 $N$ 个点（编号 $1,2…N$），$M$ 条边的有向图，求从起点 $S$ 到终点 $T$ 的第 $K$ 短路的长度，路径允许重复经过点或边。

注意： 每条最短路中至少要包含一条边。

**输入格式**

第一行包含两个整数 $N$ 和 $M$。

接下来 $M$ 行，每行包含三个整数 $A,B,L$，表示点 $A$ 与点 $B$ 之间存在有向边，且边长为 $L$。

最后一行包含三个整数 $S,T 和 K$，分别表示起点 $S$，终点 $T$ 和第 $K$ 短路。

**输出格式**

输出占一行，包含一个整数，表示第 $K$ 短路的长度，如果第 $K$ 短路不存在，则输出 `−1`。

**数据范围**

$1≤S,T≤N≤1000, 0≤M≤10^4, 1≤K≤1000, 1≤L≤100$

**输入样例**：

```
2 2
1 2 5
2 1 4
1 2 2
```

**输出样例**：

```
14
```

### 解答

易知，当点 $x$ 第 $k$ 次从优先队列队头取出时，求得的就是从起点到点 $x$ 的第 $k$ 短路代价

直接用优先队列做的时间复杂度为 $O(K(N + M) \log (N + M))$

考虑设计估价函数 `f(x)` 为 `x` 到点 `T` 的最短路距离

这样在第 K 短路中，点`x` 到点`T`的估计距离`f(x)`小于实际距离，估价函数设计成立

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

const int N = 1010, M = 20010;

int S, T, K, n, m;
int hp[N], hn[N], e[M], w[M], ne[M], idx;
int cnt[N], dist[N];
bool st[N];

void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
void dijkstra()
{
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    dist[T] = 0;
    heap.push({0, T});
    while (heap.size())
    {
        PII t = heap.top(); heap.pop();
        
        if (st[t.y]) continue;
        st[t.y] = true;

        for (int i = hn[t.y]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t.y] + w[i])
            {
                dist[j] = dist[t.y] + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}
int f(int id)
{
    return dist[id];
}
int astar()
{
    memset(cnt, 0, sizeof cnt);
    priority_queue<PIII, vector<PIII>, greater<PIII>> heap;
    heap.push({f(S), {0, S}});
    while (heap.size())
    {
        PIII t = heap.top(); heap.pop();

        int ver = t.y.y, d = t.y.x;
        cnt[ver] ++ ;
        if (cnt[T] == K) return d;
        
        for (int i = hp[ver]; ~i; i = ne[i])
        {
            int j = e[i];
            if (cnt[j] < K)
                heap.push({d + w[i] + f(j), {d + w[i], j}});
        }
    }
    return -1;
}
int main()
{
    cin >> n >> m;
    memset(hp, -1, sizeof hp);
    memset(hn, -1, sizeof hn);
    while (m -- )
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(hp, a, b, c);
        add(hn, b, a, c);
    }
    cin >> S >> T >> K;
    if (S == T) K ++ ;
    
    dijkstra();
    cout << astar() << endl;
    return 0;
}
```

## 八数码

### 题目描述

在一个 $3×3$ 的网格中，$1∼8$ 这 $8$ 个数字和一个 `X` 恰好不重不漏地分布在这 $3×3$ 的网格中。

例如：

```
1 2 3
X 4 6
7 5 8
```

在游戏过程中，可以把 `X` 与其上、下、左、右四个方向之一的数字交换（如果存在）。

我们的目的是通过交换，使得网格变为如下排列（称为正确排列）：

```
1 2 3
4 5 6
7 8 X
```

例如，示例中图形就可以通过让 `X` 先后与右、下、右三个方向的数字交换成功得到正确排列。

交换过程如下：

```
1 2 3   1 2 3   1 2 3   1 2 3
X 4 6   4 X 6   4 5 6   4 5 6
7 5 8   7 5 8   7 X 8   7 8 X
```

把 `X` 与上下左右方向数字交换的行动记录为 `u、d、l、r`

现在，给你一个初始网格，请你通过最少的移动次数，得到正确排列。

**输入格式**

输入占一行，将 $3×3$ 的初始网格描绘出来。

例如，如果初始网格如下所示：

```
1 2 3 
x 4 6 
7 5 8 
```

则输入为：`1 2 3 x 4 6 7 5 8`

**输出格式**

输出占一行，包含一个字符串，表示得到正确排列的完整行动记录

如果答案不唯一，输出任意一种合法方案即可

如果不存在解决方案，则输出 `unsolvable`

**输入样例**：

```
2  3  4  1  5  x  7  6  8 
```

**输出样例**

```
ullddrurdllurdruldr
```

### 解答

估价函数设置为所有数字在 `state` 中的位置与目标位置 `end` 中的位置的曼哈顿距离之和：

$$
f(state) = \sum_{num=1}^9 (|state_{x_{num}} - end_{x_{num}}| + |state_{y_{num}} - end_{y_{num}}|)
$$

```cpp
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
```