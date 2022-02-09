#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
const int N = 10010, SIZE = N << 2;

queue<PII> wait;
priority_queue<PII, vector<PII>, greater<PII>> task;

int n, t, m, p;
int cur_time;

struct Node
{
    int addr, size;
    int prev, next;
}node[SIZE];
int head, tail, tot;

void initialize()
{
    head = 1, tail = tot = 2;
    node[head] = {-1, 1};
    node[tail] = {n, 1};
    node[head].next = tail;
    node[tail].prev = head;
}
int insert(int p, int addr, int size)
{
    int q = ++ tot;
    node[q] = {addr, size};
    node[q].prev = p, node[q].next = node[p].next;
    node[node[p].next].prev = q, node[p].next = q;
    return q;
}
void remove(int p)
{
    node[node[p].prev].next = node[p].next;
    node[node[p].next].prev = node[p].prev;
}

bool distribute_memory(int len, int end_time)
{
    for (int i = head; i != tail; i = node[i].next)
    {
        Node &a = node[i], &b = node[node[i].next];
        int l = a.addr + a.size, r = b.addr;
        if (r - l >= len)
        {
            task.push({end_time, insert(i, l, len)});
            return true;
        }
    }
    return false;
}
void free_block(int t)
{
    while (task.size() && task.top().x <= t)
    {
        //同一时间的全部释放
        int free_time = task.top().x;
        while (task.size() && task.top().x == free_time)
        {
            remove(task.top().y);
            task.pop();
        }
        cur_time = free_time;
        //释放一轮后，处理等待队列
        while (wait.size() && distribute_memory(wait.front().x, cur_time + wait.front().y))
        {
            wait.pop();
        }
    }
}
int main()
{
    scanf("%d", &n);
    initialize();

    int cnt = 0;
    while (scanf("%d%d%d", &t, &m, &p), t || m || p)
    {
        free_block(t), cur_time = t;
        if (!distribute_memory(m, cur_time + p))
        {
            wait.push({m, p});
            cnt ++ ;
        }
    }
    free_block(2e9);
    printf("%d\n%d", cur_time, cnt);
    return 0;
}