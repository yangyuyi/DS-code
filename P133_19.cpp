#include <iostream>
#include <vector>

using namespace std;

template<class T>
class min_heap {
private:
    T *arr;
    int cur_size;
    int max_size;
    int cnt{};
public:
    explicit min_heap(int n, vector<T> src);

    ~min_heap();

    void build();

    void down(int father);

    void print();

    int get_cnt();
};

template<class T>
min_heap<T>::min_heap(const int n, vector<T> src) {
    if (n <= 0) return;
    cnt = 0;
    cur_size = 0;
    max_size = n;
    arr = new T[max_size];
    for (int i = 0; i < src.size(); i++) arr[i] = src[i];
    cur_size = src.size();
    build();
}

template<class T>
min_heap<T>::~min_heap() {
    cur_size = 0;
    max_size = 0;
    delete[]arr;
}

template<class T>
void min_heap<T>::build() {
    for (int i = cur_size / 2 - 1; i >= 0; i--) down(i);
}

template<class T>
void min_heap<T>::down(int father) {
    int son;
    T tmp = arr[father];
    while (father * 2 + 1 < cur_size) {
        son = father * 2 + 1;
        if (son < cur_size - 1 && arr[son + 1] < arr[son]) son++;
        if (tmp > arr[son]) {
            arr[father] = arr[son];
            father = son;
            cnt++;
        } else break;
    }
    arr[father] = tmp;
}

template<class T>
void min_heap<T>::print() {
    for (int i = 0; i < cur_size; i++) cout << arr[i] << ' ';
    cout << endl;
}

template<class T>
int min_heap<T>::get_cnt() {
    return cnt;
}

int main() {
    vector<char> data = {'E', 'D', 'X', 'K', 'H', 'L', 'M', 'C', 'P'};
    min_heap<char> *h;
    h = new min_heap<char>(10, data);
    cout << "Order:";
    h->print();
    cout << "shift time:";
    cout << h->get_cnt() << endl;
    return 0;
}
