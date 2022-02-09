#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <stack>

using namespace std;

string str;
unordered_map<char, int> mp = 
{
    {'-', 1},
    {'+', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
};
stack<char> ops;
stack<int> num;

int power(int a, int b)
{
    int res = 1;
    for (; b; b >>= 1)
    {
        if (b & 1) res = (long long) res * a;
        a *= a;
    }
    return res;
}
void eval()
{
    int a = num.top(); num.pop();
    int b = num.top(); num.pop();
    char op = ops.top(); ops.pop();

    int res;
    if (op == '+') res = b + a;
    else if (op == '-') res = b - a;
    else if (op == '*') res = b * a;
    else if (op == '/') res = b / a;
    else res = power(b, a);
    //printf("%d %c %d = %d\n", b, op, a, res);
    num.push(res);
}
int main()
{
    cin >> str;
    string s;
    for (int i = 0; i < str.size(); i ++ )
    {
        if (str[i] == '-' && (!i || !isdigit(s[i-1])))
        {
            if (str[i - 1] == ')') s += "+(0-1)*";
            else s += "(0-1)*";
        }
        else s += str[i];
    }
    for (int i = 0; i < s.size(); i ++ )
    {
        if (isdigit(s[i]))
        {
            int j = i, sum = 0;
            while (j < s.size() && isdigit(s[j]))
                sum = sum * 10 + s[j ++ ] - '0';
            num.push(sum);
            i = j - 1;
        }
        else if (s[i] == '(') ops.push(s[i]);
        else if (s[i] == ')')
        {
            while(ops.size() && ops.top() != '(') eval();
            if (ops.size()) ops.pop();
        }
        else
        {
            while (ops.size() && mp[s[i]] <= mp[ops.top()]) eval();
            ops.push(s[i]);
        }
    }
    while (ops.size())
    {
        if (ops.top() == '(') ops.pop();
        else eval();
    }
    cout << num.top() << endl;
    return 0;
}