---
title: 《算法竞赛进阶指南》0x16 Trie
date: 2022-2-7
categories: 算法竞赛进阶指南
tag:
- 算法竞赛进阶指南
---

# Trie基本概念

Trie，又名字典树，顾名思义是一个用于存放字符串的树，他逻辑结构上是一棵树，而不是线性表

线性表存放字符串限制了字符之间的关系，仅仅只能前后相邻，因此一般一个一维表只用于存放一个串

而树就突破了这一限制，其字符之间关系变成了“父-子”，所以一棵Trie可以存放多个串

![](https://cdn.acwing.com/media/article/image/2022/02/06/55909_921de4c087-trie1.png)

在 Trie 中，我们认为一个结点是一个字符串/状态，由从根到自身的所有边的字符构成

> **结点** 并非 **字符**，**边** 才是 **字符**，结点可以理解为 **状态** ，或 **字符串**

因此不难看出：任意两个结点的 LCA（最近公共祖先）表示两个结点的最长相等前缀

正如上述例子，借用树的性质，我们可以对 Trie 延伸出很多的结论和性质，今后会一一介绍

**Trie的板子：**

次板子可以修改成直接支持插入和删除的功能（言外之意，Trie 有时可以不需要刻意上可持久化)

```cpp
struct Trie
{
    // 假设字符串由小写字母构成
    int trie[SIZE][26], tot = 0;
    int end[SIZE];  //该节点结尾的字符串是否存在
    // Trie的插入
    void insert(char* str)
    {
        int len = strlen(str), p = 1;
        for (int k = 0; k < len; k ++ )
        {
            int ch = str[k] - 'a';
            if (trie[p][ch] == 0) trie[p][ch] = ++ tot;
            p = trie[p][ch];
        }
        end[p] = true;
    }

    // Trie的检索
    bool search(char* str)
    {
        int len = strlen(str), p = 1;
        for (int k = 0; k < len; k ++ )
        {
            p = trie[p][str[k] - 'a'];
            if (p == 0) return false;
        }
        return end[p];
    }
} trie;
```

# Trie 的应用

- 检索字符串
  - 板子基本功能
- AC 自动机
  - KMP 是作用于 线性表 的模式匹配算法
  - AC自动机 是作用于 树 的模式匹配算法
  - 两者理论基础都是在失配时找最长相等前后缀，AC 自动机会在以后章节详细讲解
- 维护异或极值
  - 边插边询问即可
- 维护异或和
  - 插入 & 删除
    - 板子基本功能
  - 全局加一
    - 从低位到高位开始找第一个出现的 `0`，把它变成 `1`，然后这个位置后面的 `1` 都变成 `0` 即可 
- 01-trie 合并
  - 思路类似线段树合并，以后细讲
- 可持久化字典树
  - 同上，以后章节细讲

# 习题

## 前缀统计

### 题目描述

给定 $N$ 个字符串 $S_1,S_2…S_N$，接下来进行 $M$ 次询问，每次询问给定一个字符串 $T$，求 $S_1∼S_N$ 中有多少个字符串是 $T$ 的前缀。

输入字符串的总长度不超过 $10^6$，仅包含小写字母。

**输入格式**

第一行输入两个整数 $N, M$。

接下来 $N$ 行每行输入一个字符串 $S_i$。

接下来 $M$ 行每行一个字符串 $T$ 用以询问。

**输出格式**

对于每个询问，输出一个整数表示答案。

每个答案占一行。

**数据范围**

$1≤N,M≤10^5$

**输入样例**：

```
3 2
ab
bc
abc
abc
efg
```

**输出样例**：

```
2
0
```

### 解析

字典树的板子题，在查找时，顺便统计一下前缀中的字符串

```cpp
int search(char *str)
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
```

## 最大异或对

### 题目描述

在给定的 $N$ 个整数 $A_1，A_2,…,A_N$ 中选出两个进行 `xor`（异或）运算，得到的结果最大是多少？

**输入格式**

第一行输入一个整数 $N$。

第二行输入 $N$ 个整数 $A_1～A_N$。

**输出格式**

输出一个整数表示答案。

**数据范围**

$1≤N≤10^5,\ 0≤A_i<2^{31}$

**输入样例**：

```
3
1 2 3
```

**输出样例**：

```
3
```

### 解析

注意，启发式策略下，我们希望异或对尽可能大，那么就是让高位尽可能不同

因此存储该字符串时，我们希望从高位往低位存储，这样查询时，在高位尽可能错开就错开

```cpp
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
```

## 最长异或值路径

### 题目描述

给定一个树，树上的边都具有权值。

树中一条路径的异或长度被定义为路径上所有边的权值的异或和：

$$
length_{xor}(p) = ⊕_{e\in p} w(e)
$$

⊕ 为异或符号。

给定上述的具有 $n$ 个节点的树，你能找到异或长度最大的路径吗？

**输入格式**

第一行包含整数 $n$，表示树的节点数目。

接下来 $n−1$ 行，每行包括三个整数 $u，v，w$，表示节点 $u$ 和节点 $v$ 之间有一条边权重为 $w$。

**输出格式**

输出一个整数，表示异或长度最大的路径的最大异或和。

**数据范围**

$1≤n≤100000,\ 0≤u,v<n,\ 0≤w<2^{31}$

**输入样例**：

```
4
0 1 3
1 2 4
1 3 6
```

**输出样例**：

```
7
```

**样例解释**

样例中最长异或值路径应为 `0->1->2`，值为 $7 = 3⊕4$

### 解析

本题解法非常的秒，用到了异或的性质：$x ⊕ x = 0$

因此，求树上任意两点的异或路径长度 等价于 求他们各自到根节点的异或路径长度的异或值

证明如下，分类讨论即可：

**第一种情况：根节点在两个点的路径之上**

那么两点的异或路径长度就是各自到根节点的异或路劲长度的异或值

**第二种情况：根节点不在两个点的路径之上**

则任意一个点到根节点的路径都是先到两点的 LCA，再从 LCA 出发到达根节点

而从 LCA 出发到根节点的这段路径有两条，异或运算具有交换律，因此易得该段异或值为 $0$

下面给出数学证明，写出两个点各自到根节点的异或路径长：

$$
\begin{cases}
length_{xor}(a) &= [⊕_{e\in(a \to LCA(a,b))} w(e)] ⊕ [⊕_{e\in (LCA(a,b) \to root)} w(e)] \\\\
length_{xor}(b) &= [⊕_{e\in(b \to LCA(a,b))} w(e)] ⊕ [⊕_{e\in (LCA(a,b) \to root)} w(e)]
\end{cases}
$$

两者取异或可得：$length_{xor}(a) ⊕ length_{xor}(b) = [⊕_{e\in(a \to LCA(a,b))} w(e)] ⊕ [⊕_{e\in(b \to LCA(a,b))} w(e)]$

得证

因此原问题就等价于：求所有点到根节点的异或路径中，选出两条，使得两者异或值最大

就是 Trie 的板子了

```cpp
struct Trie
{
    int trie[SIZE][2], tot;
    void insert(int num)
    {
        int p = 0;
        for (int i = 30; ~i; i -- )
        {
            int ch = num >> i & 1;
            if (!trie[p][ch]) trie[p][ch] = ++ tot;
            p = trie[p][ch];
        }
    }
    int query(int num)
    {
        int res = 0, p = 0;
        for (int i = 30; ~i; i -- )
        {
            int ch = num >> i & 1;
            if (!trie[p][!ch]) p = trie[p][ch];
            else
            {
                res += 1 << i;
                p = trie[p][!ch];
            }
        }
        return res;
    }
}trie;
int dist[N];

void dfs(int u, int xor_len, int fa)
{
    dist[u] = xor_len;
    for (int i = head[u]; i; i = nxt[i])
    {
        if (ver[i] == fa) continue;
        dfs(ver[i], xor_len ^ edge[i], u);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i ++ )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a + 1, b + 1, c), add(b + 1, a + 1, c);
    }
    dfs(1, 0, 0);
    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int val = dist[i];
        res = max(res, trie.query(val));
        trie.insert(val);
    }
    printf("%d\n", res);
    return 0;
}
```