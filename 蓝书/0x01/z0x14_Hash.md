---
title: 《算法竞赛进阶指南》0x14 Hash
date: 2022-2-5
categories: 算法竞赛进阶指南
tag:
- 算法竞赛进阶指南
---

# Hash表基本概念

Hash 表又称散列表，一般由Hash函数与链表结构共同实现

与离散化思想类似，当我们要对若干复杂信息进行统计时，可以用 Hash函数 把这些复杂信息映射到一个容易维护的值域内

因为值域变简单、范围变小，可能造成不同的原始信息被 Hash函数 映射为相同的值，处理该冲突的方法有：

1. “闭散列法”（开放寻址法）：闭散列方法把所有记录直接存储在散列表中，如果发生冲突则根据某种方式继续进行探查
2. **“开散列法” （拉链法）**：开散列法是在每个存放数据的地方开一个链表，如果有多个键值索引到同一个地方，只用把他们都放到那个位置的链表里就行了，查询的时候需要把对应位置的链表整个扫一遍，对其中的每个数据比较其键值与查询的键值是否一致

**Hash表的两个基本操作** ：

1. 计算 Hash函数 的值
2. 定位到对应链表中依次遍历、比较

其他所有操作都是基于上述两个操作的

# 字符串哈希

Hash 的核心思想在于，将输入映射到一个值域较小、可以方便比较的范围

> 这里的“值域较小”在不同情况下意义不同
> 
> 在 哈希表 中，值域需要小到能够接受线性的空间与时间复杂度
> 
> 在字符串哈希中，值域需要小到能够快速比较（$10^9$、 $10^{18}$ 都是可以快速比较的）
> 
> 同时，为了降低哈希冲突率，值域也不能太小

下面介绍的 字符串Hash函数 把一个任意长度的字符串映射成一个非负整数，并且其冲突概率几乎为零

**取一固定值 $P$，把字符串看做 $P$ 进制数，并分配一个大于 $0$ 的数值，代表每种字符**

一般来说，分配的数值都远小于 $P$，例如，对于小写字符构成的字符串，可以令 $a=1,b=2,\cdots$

**取一固定值 $M$，求出 $P$ 进制数对 $M$ 的余数，作为该字符串的 Hash值**

> 【注】对于一个字符，其高低位和下标是反过来的  

对于字符串 $S = \overline{s_{n}s_{n-1}\cdots s_2s_1}$，其哈希值为：

$$
H(S) = s_1 \times P^{n-1} + s_2 \times P^{n-2} + \cdots + s_{n-1} \times P + s_n
$$

一般来说，**$P = 131$ 或 $P = 13331$**，此时 Hash 值产生冲突的概率极低

只要 Hash值 相同，我们就可以认为原字符串是相等的

通常**取 $M = 2^{64}$**，即直接**使用 unsigned long long 类型**存储这个 Hash值，让计算机自动取模

**如何递推求解字符串的哈希值**

基于如下的理论，对于一个字符串 $S=\overline{s_{1} s_2 \cdots s_n}$，我们在后面添加一个字符 $c$，则新哈希值为：

$$
H(\overline{Sc}) =  s_1 \times P^{n} + s_2 \times P^{n-1} + \cdots + s_n \times P + c
$$

固有递推式：$H(\overline{Sc}) = (H(S) \times P + value(c)) \bmod M$

由如上递推式，我们可以从低位开始，对一个字符串进行遍历，并同时生成其任意前缀的哈希值

**如何求解字符串任意子串的哈希值**

基于上述递推，我们对整个字符串哈希完成后，同时获得了两个数组：$H[N], P[N]$

因此我们可以在 $O(1)$ 的时间内，获得范围内任意 **字符串的前缀哈希值** 和 **$P$ 的 $n$ 次幂**

对于已知哈希值的字符串 $\overline{ST}$，求解其后缀子串 $T$ 的哈希值，将其分解成多项式有：

$$
\overline{ST} = s_1 \times P^{n + m - 1} + \cdots + s_{n-1} \times P^{m+1} + s_n \times P^{m} + t_1 \times P^{m-1} + \cdots  + t_{m-1} \times P + t_m
$$

简单推导易得公式：$H(T) = (H(\overline{ST}) - H(S) \times P^m) \bmod M$ ，其中 $m$ 为 $T$ 的长度

```cpp
typedef unsigned long long ULL;
const int P = 131; //131 or 13331
ULL f[N], p[N];
ULL get_hash(int l, int r)
{
    return f[r] - f[l - 1] * p[r - l + 1];
}
void initialize_hash()
{
    p[0] = 1;
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = p[i - 1] * P;
        f[i] = f[i - 1] * p + str[i];
    }
}
```

# 习题

## 雪花雪花雪花

### 题目描述

有 $N$ 片雪花，每片雪花由六个角组成，每个角都有长度。

第 $i$ 片雪花六个角的长度从某个角开始顺时针依次记为 $a_{i,1},a_{i,2},…,a_{i,6}$。

因为雪花的形状是封闭的环形，所以从任何一个角开始顺时针或逆时针往后记录长度，得到的六元组都代表形状相同的雪花。

例如 $a_{i,1},a_{i,2},…,a_{i,6}$ 和 $a_{i,2},…,a_{i,6},a_{i,1}$ 就是形状相同的雪花。

$a_{i,1},a_{i,2},…,a_{i,6}$ 和 $a_{i,6},a_{i,5},…,a_{i,1}$ 也是形状相同的雪花。

我们称两片雪花形状相同，当且仅当它们各自从某一角开始顺时针或逆时针记录长度，能得到两个相同的六元组。

求这 $N$ 片雪花中是否存在两片形状相同的雪花。

**输入格式**

第一行输入一个整数 $N$，代表雪花的数量。

接下来 $N$ 行，每行描述一片雪花。

每行包含 $6$ 个整数，分别代表雪花的六个角的长度（这六个数即为从雪花的随机一个角顺时针或逆时针记录长度得到）。

同行数值之间，用空格隔开。

**输出格式**

如果不存在两片形状相同的雪花，则输出：`No two snowflakes are alike.`

如果存在两片形状相同的雪花，则输出：`Twin snowflakes found.`

**数据范围**

$1≤N≤100000, 0≤ai,j<10000000$

**输入样例**：

```
2
1 2 3 4 5 6
4 3 2 1 6 5
```

**输出样例**：

```
Twin snowflakes found.
```

### 解析

本题的问题是如何将同类集合的雪花存下来，映射到一个更小的范围内，便于查询

蓝书上用了累加累乘值之和作为一个字符串的哈希值，y总用了字符串的最小表示法进行的哈希

蓝书解法直接看书，y总解法见下一章节的字符串最小表示法

本题代码：

```cpp
for (int i = 1; i <= n; i ++ )
{
    vector<int> snow(6), isnow(6);
    for (int j = 0; j < 6; j ++ ) scanf("%d", &snow[j]), isnow[5 - j] = snow[j];
    get_min(snow);
    get_min(isnow);
    snows[i] = min(snow, isnow);
}
sort(snows + 1, snows + n + 1);

bool flag = false;
for (int i = 1; i < n; i ++ )
    if (snows[i] == snows[i + 1])
        flag = true;
puts(flag ? "Twin snowflakes found." : "No two snowflakes are alike.");
```

## 兔子与兔子

### 题目描述

很久很久以前，森林里住着一群兔子。

有一天，兔子们想要研究自己的 DNA 序列。

我们首先选取一个好长好长的 DNA 序列（小兔子是外星生物，DNA 序列可能包含 $26$ 个小写英文字母）。

然后我们每次选择两个区间，询问如果用两个区间里的 DNA 序列分别生产出来两只兔子，这两个兔子是否一模一样。

注意两个兔子一模一样只可能是他们的 DNA 序列一模一样。

**输入格式**

第一行输入一个 DNA 字符串 $S$。

第二行一个数字 $m$，表示 $m$ 次询问。

接下来 $m$ 行，每行四个数字 $l_1,r_1,l_2,r_2$，分别表示此次询问的两个区间，注意字符串的位置从 $1$ 开始编号。

**输出格式**

对于每次询问，输出一行表示结果。

如果两只兔子完全相同输出 Yes，否则输出 No（注意大小写）。

**数据范围**

$1≤length(S),m≤1000000$

**输入样例**：

```
aabbaabb
3
1 3 5 7
1 3 6 8
1 2 1 2
```

**输出样例**：

```
Yes
No
Yes
```

### 解析

字符串哈希的板子题

```cpp
scanf("%s", str + 1);
n = strlen(str + 1);
initialize();
scanf("%d", &m);
while (m -- )
{
    int l1, r1, l2, r2;
    scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
    puts(get_hash(l1, r1) == get_hash(l2, r2) ? "Yes" : "No");
}
```

## 回文子串的最大长度

### 题目描述

如果一个字符串正着读和倒着读是一样的，则称它是回文的。

给定一个长度为 $N$ 的字符串 $S$，求他的最长回文子串的长度是多少。

**输入格式**

输入将包含最多 $30$ 个测试用例，每个测试用例占一行，以最多 $10^6$ 个小写字符的形式给出。

输入以一个以字符串 `END` 开头的行表示输入终止。

**输出格式**

对于输入中的每个测试用例，输出测试用例编号和最大回文子串的长度（参考样例格式）。

每个输出占一行。

**输入样例**：

```
abcbabcbabcba
abacacbaaaab
END
```

**输出样例**：

```
Case 1: 13
Case 2: 6
```

### 解析

最长回文子串，是学 “马拉车” 的板子题，可以在线性的时间内完成求解

本篇讲用字符串哈希来进行求解，时间复杂度次于马拉车，为 $O(n\log n)$

根据回文子串的定义，不难想到暴力做法，先枚举子串中点，然后向两侧延伸找到相等的最长长度

枚举好终点后，不难发现答案长度具有单调性，即大于最长长度必然前后缀不相等，小于等于则相等

因此我们可以结合该单调性，二分出最长长度，二分的过程中判断前后是否构成回文，可以用字符串哈希

即可在 $O(1)$ 的时间内，实现二分结果的判定

这题还要注意边界，回文子串可能是奇数串也可能是偶数串（没中点）

因此在预处理时，我们可以把每两个字母之间放入一个 `#` 号隔开，这样所有情况都可以处理成奇数情况

```cpp
void initialize()
{
    p[0] = 1;
    f[0] = g[n + 1] = 0;
    for (int i = 1, j = n; i <= n; i ++ , j -- )
    {
        p[i] = p[i - 1] * P;
        f[i] = f[i - 1] * P + s[i];
        g[i] = g[i - 1] * P + s[j];
    }
}
ULL get_hash(ULL h[], int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}
void solve()
{
    n = strlen(s + 1);
    for (int i = n << 1; i; i -= 2)
    {
        s[i] = s[i / 2];
        s[i - 1] = '#';
    }
    n <<= 1;
    initialize();

    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int l = 0, r = min(i - 1, n - i);
        while (l < r)   //[i - mid, i] [i, i + mid] -> [n+1-(i+mid), n+1-i]
        {
            int mid = (l + r + 1) >> 1;
            ULL lval = get_hash(f, i - mid, i);
            ULL rval = get_hash(g, n + 1 - (i + mid), n + 1 - i);
            if (lval == rval) l = mid; else r = mid - 1;
        }
        if (s[i - l] != '#') l ++ ;
        res = max(res, l);
    }
    printf("%d\n", res);
}
```

## 后缀数组

### 题目描述

后缀数组 (SA) 是一种重要的数据结构，通常使用倍增或者 DC3 算法实现，这超出了我们的讨论范围。

在本题中，我们希望使用快排、Hash 与二分实现一个简单的 $O(nlog^2n)$ 的后缀数组求法。

详细地说，给定一个长度为 $n$ 的字符串 $S$（下标 $0∼n−1$），我们可以用整数 $k(0≤k<n)$ 表示字符串 $S$ 的后缀 $S(k∼n−1)$。

把字符串 $S$ 的所有后缀按照字典序排列，排名为 $i$ 的后缀记为 $SA[i]$。

额外地，我们考虑排名为 $i$ 的后缀与排名为 $i−1$ 的后缀，把二者的最长公共前缀的长度记为 $Height[i]$。

我们的任务就是求出 $SA$ 与 $Height$ 这两个数组。

**输入格式**

输入一个字符串，其长度不超过 $3\times 10^5$。

字符串由小写字母构成。

**输出格式**

第一行为数组 $SA$，相邻两个整数用 $1$ 个空格隔开。

第二行为数组 $Height$，相邻两个整数用 $1$ 个空格隔开，我们规定 $Height[1]=0$。

**输入样例**：

```
ponoiiipoi
```

**输出样例**：

```
9 4 5 6 2 8 3 1 7 0
0 1 2 1 0 0 2 1 0 2
```

### 解析

暴力快排的时间复杂度为 $O(n^2 \log n)$ 因为字符串每一次比较的时间复杂度为 $O(len(s))$

基于比较的排序算法时间复杂度下界为 $O(n\log n)$ 因此能优化的只有字符串的比较方式

基于上一题最长回文子串解法的启发，我们可以在进行字符串比较时用哈希 + 二分的手段优化到 $O(\log len(s))$

通过字符串哈希和二分迅速找到最长相等前缀，然后比较最后一个不相等的字符，决定两个子串的大小

总时间复杂度为 $O(n\log^2 n)$

```cpp
int get_max_common_prefix(int a, int b) //二分两个子数组最长前缀
{
    int l = 0, r = min(n + 1 - a, n + 1 - b);
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (get_hash(a, a + mid - 1) == get_hash(b, b + mid - 1)) l = mid;
        else r = mid - 1;
    }
    return r;
}
bool cmp(int a, int b)  //比较后缀字符串 str[a...n] 和 str[b...n] 的大小
{
    int len = get_max_common_prefix(a, b);
    int a_val = a + len > n ? 0 : str[a + len];
    int b_val = b + len > n ? 0 : str[b + len];
    return a_val < b_val;
}
```