#include <iostream>

using namespace std;

template<class T>
class Node {
public:
    T data;
    Node *next;

    Node() {
        this->next = NULL;
    }

    Node(const T data, Node<T> *next) {
        this->data = data;
        this->next = next;
    }
};

template<class T>
class linkQueue {
private:
    Node<T> *rear;
public:
    linkQueue();

    ~linkQueue();

    bool isEmpty();

    bool in(const T item);

    bool out(T &item);

    void clear();
};

template<class T>
linkQueue<T>::linkQueue() {
    rear = NULL;
}

template<class T>
linkQueue<T>::~linkQueue() {
    clear();
}

template<class T>
bool linkQueue<T>::isEmpty() {
    return rear == NULL;
}

template<class T>
bool linkQueue<T>::in(const T item) {
    if (isEmpty()) {
        Node<T> *node;
        node = new Node<T>(item, rear);
        node->next = node;
        rear = node;
        return true;
    }

    Node<T> *node;
    node = new Node<T>(item, rear->next);
    rear->next = node;
    rear = node;
    return true;
}

template<class T>
bool linkQueue<T>::out(T &item) {
    if (isEmpty()) {
        cout << "Illegal Operation:The queue is empty." << endl;
        return false;
    }

    Node<T> *front;
    front = rear->next;
    item = front->data;
    if (front->next == front) {
        rear = NULL;
        delete front;
        return true;
    }
    rear->next = front->next;
    delete front;
    return true;
}

template<class T>
void linkQueue<T>::clear() {
    Node<T> *tmp;
    while (rear != NULL) {
        tmp = rear;
        rear = rear->next;
        delete tmp;
    }
    rear = NULL;
}

int main() {
    linkQueue<int> *q;
    q = new linkQueue<int>();

    int x = 0;
    q->out(x);
    cout << x << endl;
    q->in(0);
    q->in(1);
    q->in(2);
    q->out(x);
    cout << x << endl;
    q->out(x);
    cout << x << endl;
    q->out(x);
    cout << x << endl;
    return 0;
}
