#include <iostream>

using namespace std;

template<class T>
class List {
public:
    virtual void print() = 0;

    virtual bool append(const T value) = 0;

    virtual bool get_del(const int pos, T &value) = 0;

    virtual bool isEmpty() = 0;

    void work(const int n, const int m, const int s) {
        int pos = s - 1;
        T value;
        cout << "The list is ";
        for (int i = 0; i < n; i++) {
            get_del((pos + m - 1) % (n - i), value);
            pos = (pos + m - 1) % (n - i);
            cout << value << ' ';
        }
        cout << endl;
    }
};

template<class T>
class arrList : public List<T> {
private:
    T *list;
    int len;
    int maxSize;
public:
    arrList(int size);

    ~arrList();

    void print() override;

    int length();

    bool append(const T value) override;

    bool get_del(const int pos, T &value) override;

    bool isEmpty() override;
};

template<class T>
arrList<T>::arrList(int size) {
    maxSize = size;
    list = new T[maxSize];
    len = 0;
}

template<class T>
arrList<T>::~arrList() {
    delete[]list;
}

template<class T>
bool arrList<T>::append(const T value) {
    if (len >= maxSize - 1) {
        cout << "list will be overflow" << endl;
        return false;
    }
    list[len++] = value;
    return true;
}

template<class T>
bool arrList<T>::get_del(const int pos, T &value) {
    if (isEmpty()) {
        cout << "no element to delete" << endl;
        return false;
    }
    if (pos < 0 || pos > len - 1) {
        cout << "illegal position" << endl;
    }

    value = list[pos];
    for (int i = pos; i < len - 1; i++) list[i] = list[i + 1];
    len--;
    return true;
}

template<class T>
bool arrList<T>::isEmpty() {
    return len <= 0;
}

template<class T>
int arrList<T>::length() {
    return len;
}

template<class T>
void arrList<T>::print() {
    if (isEmpty()) {
        cout << "None" << endl;
        return;
    }
    for (int i = 0; i < len; i++) {
        cout << list[i] << ' ';
    }
    cout << endl;
}

template<class T>
class Node {
public:
    T data;
    Node<T> *next;

    Node() {
        this->data = 0;
        this->next = NULL;
    }

    Node(T data, Node<T> *next) {
        this->data = data;
        this->next = next;
    }
};

template<class T>
class linkList : public List<T> {
private:
    Node<T> *head;
    Node<T> *tail;

    Node<T> *setPos(const int pos);

public:
    linkList();

    ~linkList();

    void print() override;

    bool append(const T value) override;

    bool get_del(const int pos, T &value) override;

    bool isEmpty() override;
};

template<class T>
linkList<T>::linkList() {
    head = tail = new Node<T>();
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
bool linkList<T>::append(const T value) {
    if (isEmpty()) {
        Node<T> *node;
        node = new Node<T>(value, head->next);
        head->next = node;
        tail = node;
        return true;
    }

    Node<T> *node;
    node = new Node<T>(value, NULL);
    tail->next = node;
    tail = node;
    return true;
}

template<class T>
bool linkList<T>::get_del(const int pos, T &value) {
    if (isEmpty()) {
        value = 0;
        cout << "no element to delete" << endl;
        return false;
    }

    Node<T> *pre, *node;
    if ((pre = setPos(pos - 1)) == NULL || pre == tail) {
        value = 0;
        cout << "illegal position" << endl;
        return false;
    }

    node = pre->next;
    value = node->data;
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

template<class T>
bool linkList<T>::isEmpty() {
    return head == tail;
}

template<class T>
Node<T> *linkList<T>::setPos(const int pos) {
    if (pos == -1) return head;

    int i = 0;
    Node<T> *node = head->next;
    while (node != NULL && i < pos) {
        node = node->next;
        i++;
    }
    return node;
}

template<class T>
void linkList<T>::print() {
    Node<T> *tmp = head->next;
    if (isEmpty()) cout << "None" << endl;
    while (tmp != NULL) {
        cout << tmp->data << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

int main() {
    int n = 10, m = 3, s = 1;
    cout << "--------Josephus Problem Calculator-------" << endl;
    cout << "Please enter the scale of data" << endl;
    cout << "First,there are n men standing in a circle waiting to be executed." << endl;
    cout << "number n=";
    cin >> n;
    cout << "Second, every m-th man will be executed going around the circle." << endl;
    cout << "number m=";
    cin >> m;
    cout << "Last, this game will start at the s-th man." << endl;
    cout << "number s=";
    cin >> s;
    while (s > n || s < 1) {
        cout << "number s is illegal.s should be between 1 and n." << endl;
        cin >> s;
    }
    int mode;
    cout << "Enter 0 or 1 to choose the data structure" << endl;
    cout << "0-arrList 1-lnkList" << endl;
    cout << "[0/1] you choose ";
    cin >> mode;
    while (!((mode == 0) || (mode == 1))) {
        cout << "illegal input.Please reenter the number you choose" << endl;
        cin >> mode;
    }
    if (mode == 0) {
        arrList<int> *arr;
        arr = new arrList<int>(n + 10);
        for (int i = 1; i <= n; i++) arr->append(i);
        arr->work(n, m, s);
    } else {
        linkList<int> *lnk;
        lnk = new linkList<int>();
        for (int i = 1; i <= n; i++) lnk->append(i);
        lnk->work(n, m, s);
    }
    return 0;
}
