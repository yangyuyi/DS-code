#include <iostream>

using namespace std;

template<class T>
class arrStack {
private:
    int top1;
    int top2;
    int maxSize;
    T *stack;
public:
    arrStack(const int n);

    ~arrStack();

    bool isFull();

    bool pop(const int index, T &value);

    bool push(const int index, const T value);
};

template<class T>
arrStack<T>::arrStack(const int n) {
    top1 = -1;
    top2 = n;
    maxSize = n;
    stack = new T[maxSize];
}

template<class T>
arrStack<T>::~arrStack() {
    delete[]stack;
}

template<class T>
bool arrStack<T>::isFull() {
    return (top2 == top1 + 1);
}

template<class T>
bool arrStack<T>::pop(const int index, T &value) {
    if (index == 1) {
        if (top1 == -1) {
            cout << "Stack is empty." << endl;
            return false;
        }
        value = stack[top1--];
        return true;
    }
    if (index == 2) {
        if (top2 == maxSize) {
            cout << "Stack is empty." << endl;
            return false;
        }
        value = stack[top2--];
        return true;
    }
    cout << "wrong index" << endl;
    return false;
}

template<class T>
bool arrStack<T>::push(const int index, const T value) {
    if (isFull()) {
        cout << "Stack is full." << endl;
        return false;
    }

    if (index == 1) stack[++top1] = value;
    if (index == 2) stack[++top2] = value;
    return true;
}

int main() {
    int n = 10;
    arrStack<int> st(n);

    st.push(1, 0);
    st.push(2, 0);
    st.push(1, 1);
    st.push(2, 1);
    for (int i = 2; i < 5; i++) st.push(1, i);
    int x;
    for (int i = 0; i < 5; i++) {
        st.pop(1, x);
        cout << x << endl;
    }
    return 0;
}
