# 基础算法

## 位运算

### 子集遍历

```cpp
// 遍历 u 的非空子集
for (int s = u; s; s = (s - 1) & u)
{
  // s 是 u 的一个非空子集
}
```

### lowbit运算

```cpp
int lowbit(int u)
{
    return u & -u;
}
```

### 快速幂

```cpp
int power(int a, int b, int p)
{
    int res = 1 % p;
    for (; b; b >>= 1)
    {
        if (b & 1) res = (long long) res * a % p;
        a = (long long) a * a % p;
    }
    return res;
}
```

### 龟速乘(64位整数乘法)

```cpp
long long mul(long long a, long long b, long long p)
{
    long long res = 0;
    for (; b; b >>= 1)
    {
        if (b & 1) res = (res + a) % p;
        a = a * 2 % p;
    }
    return res;
}
long long mul(long long a, long long b, long long p)
{
    a %= p, b %= p;
    long long c = (long double) a * b / p;
    long long ans = a * b - c * p;
    return (ans % p + p) % p;
}
```

## 
