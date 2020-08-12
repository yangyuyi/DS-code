#include <iostream>

using namespace std;

template<class T>
class arrQueue {
private:
    int front;
    int maxSize;
    int count;
    T *Q;

public:
    arrQueue(const int m);

    ~arrQueue();

    bool isEmpty();

    bool isFull();

    bool in(const T item);

    bool out(T &item);
};

template<class T>
arrQueue<T>::arrQueue(const int m) {
    maxSize = m;
    front = 0;
    count = 0;
    Q = new T[maxSize];
}

template<class T>
arrQueue<T>::~arrQueue() {
    delete[]Q;
}

template<class T>
bool arrQueue<T>::isEmpty() {
    return count == 0;
}

template<class T>
bool arrQueue<T>::in(const T item) {
    if (isFull()) {
        cout << "illegal operation:The queue is full." << endl;
        return false;
    }
    Q[(front + count) % maxSize] = item;
    count++;
    return true;
}

template<class T>
bool arrQueue<T>::out(T &item) {
    if (isEmpty()) {
        cout << "illegal operation:The queue is empty." << endl;
        return false;
    }
    item = Q[front];
    front = (front + 1) % maxSize;
    count--;
    return true;
}

template<class T>
bool arrQueue<T>::isFull() {
    return count == maxSize;
}

int main() {
    int m = 5;
    int x;
    arrQueue<int> *q;
    q = new arrQueue<int>(m);
    q->in(0);
    q->out(x);
    cout << x << endl;
    q->out(x);
    cout << x << endl;
    q->in(1);
    q->in(2);
    q->in(3);
    q->in(4);
    q->in(5);
    q->in(6);
    while (!q->isEmpty()) {
        int num;
        q->out(num);
        cout << num << endl;
    }
    return 0;
}
