class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        stkmin.push(INF);
    }

    void push(int x) {
        stkini.push(x);
        stkmin.push(min(x, getMin()));
    }

    void pop() {
        stkini.pop();
        stkmin.pop();
    }

    int top() {
        return stkini.top();
    }

    int getMin() {
        return stkmin.top();
    }
private:
    stack<int> stkini, stkmin;
    int INF = 1e9;
};