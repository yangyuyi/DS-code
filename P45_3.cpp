#include <iostream>

using namespace std;

template<class T>
class Node {
public:
    T data;
    Node<T> *next;

    Node() {
        this->data = 0;
        this->next = NULL;
    }

    Node(const T data, Node<T> *next = NULL) {
        this->data = data;
        this->next = next;
    }
};

template<class T>
class linkList {
private:
    Node<T> *head;
    Node<T> *tail;
public:
    linkList();

    ~linkList();

    void print();

    void add(T value);

    bool delet(Node<int> *pre, const Node<T> *node);

    bool del(const T min, const T max);
};

template<class T>
linkList<T>::linkList() {
    head = tail = new Node<T>;
}

template<class T>
linkList<T>::~linkList() {
    Node<T> *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<class T>
void linkList<T>::add(T value) {
    if (head == tail) {
        Node<T> *node;
        node = new Node<T>(value, head->next);
        head->next = node;
        tail = node;
        return;
    }

    Node<T> *pre = head;
    Node<T> *p = head->next;
    while (p != NULL && p->data < value) {
        pre = p;
        p = p->next;
    }
    Node<T> *node;
    node = new Node<T>(value, p);
    pre->next = node;
    if (pre == tail) tail = node;
}

template<class T>
bool linkList<T>::del(const T min, const T max) {
    if (min >= max) {
        cout << "section illegal" << endl;
        return false;
    }

    Node<T> *tmp = head->next;
    Node<T> *pre = head;
    while ((tmp != NULL) && (tmp->data < max)) {
        if (tmp->data <= min) {
            pre = tmp;
            tmp = tmp->next;
        } else {
            delet(pre, tmp);
            tmp = pre->next;
        }
    }
    return true;
}

template<class T>
void linkList<T>::print() {
    Node<T> *tmp = head->next;
    if (tmp == NULL) cout << "None" << endl;
    while (tmp != NULL) {
        cout << tmp->data << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

template<class T>
bool linkList<T>::delet(Node<int> *pre, const Node<T> *node) {
    if (node == NULL) {
        cout << "delete error" << endl;
        return false;
    }
    
    if (node == tail) {
        tail = pre;
        pre->next = NULL;
        delete node;
    } else {
        pre->next = node->next;
        delete node;
    }
    return true;
}

int main() {
    linkList<int> *lnk;
    lnk = new linkList<int>();
    lnk->add(19);
    lnk->print();
    lnk->add(7);
    lnk->print();
    lnk->add(11);
    lnk->print();
    lnk->add(2);
    lnk->print();
    lnk->add(13);
    lnk->print();
    lnk->add(17);
    lnk->print();
    lnk->add(3);
    lnk->print();
    lnk->add(5);
    lnk->print();
    lnk->del(1, 20);
    lnk->print();
    return 0;
}
