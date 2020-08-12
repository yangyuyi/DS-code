#include <iostream>
#include <algorithm>

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

    linkList(T arr[], const int l);

    ~linkList();

    void print();

    void append(T value);

    Node<T> *getNode(const int pos);

    linkList<T> *intersection(linkList<T> *link);
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
void linkList<T>::append(T value) {
    if (head == tail) {
        Node<T> *node;
        node = new Node<T>(value, head->next);
        head->next = node;
        tail = node;
        return;
    }

    Node<T> *node;
    node = new Node<T>(value, NULL);
    tail->next = node;
    tail = node;
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
linkList<T>::linkList(T *arr, const int l) {
    head = tail = new Node<T>;
    sort(arr, arr + l);
    for (int i = 0; i < l; i++) {
        append(arr[i]);
    }
}

template<class T>
linkList<T> *linkList<T>::intersection(linkList<T> *link) {
    linkList<T> *link_result;
    link_result = new linkList();
    T value1, value2;
    Node<T> *node1, *node2;
    node1 = head->next;
    node2 = link->getNode(0);

    while (node1 != NULL && node2 != NULL) {
        value1 = node1->data;
        value2 = node2->data;
        if (value1 == value2) {
            link_result->append(value1);
            node1 = node1->next;
            node2 = node2->next;
        } else if (value1 > value2) {
            node2 = node2->next;
        } else node1 = node1->next;
    }
    return link_result;
}

template<class T>
Node<T> *linkList<T>::getNode(const int pos) {
    if (pos == -1) {
        return head;
    }

    int i = 0;
    Node<T> *p;
    p = head->next;
    while (p != NULL && i < pos) {
        p = p->next;
        i++;
    }
    return p;
}

int main() {
    int arr1[] = {0, 3, 45, 2, 4};
    linkList<int> *link_A;
    link_A = new linkList<int>(arr1, (int) sizeof(arr1) / sizeof(*arr1));
    link_A->print();
    int arr2[] = {0, 3, 45, 2, 5};
    linkList<int> *link_B;
    link_B = new linkList<int>(arr2, (int) sizeof(arr2) / sizeof(*arr2));
    link_B->print();
    linkList<int> *link_C;
    link_C = link_A->intersection(link_B);
    link_C->print();
    return 0;
}
