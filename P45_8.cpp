#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

template<class T>
class arrList {
private:
    T *list;
    int len;
    int maxSize;
public:
    arrList(const int size);

    arrList(T arr[], const int l, const int size);

    ~arrList();

    void print();

    int length();

    bool append(const T value);

    bool getValue(const int pos, T &value);

    arrList<T> *intersection(arrList<T> *arr);
};

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
arrList<T>::arrList(T *arr, const int l, const int size) {
    sort(arr, arr + l);
    maxSize = max(l, size);
    len = l;
    list = new T[maxSize];
    memcpy(list, arr, sizeof(*arr) * l);
}

template<class T>
arrList<T>::arrList(const int size) {
    maxSize = size;
    len = 0;
    list = new T[maxSize];
}

template<class T>
int arrList<T>::length() {
    return len;
}

template<class T>
arrList<T> *arrList<T>::intersection(arrList<T> *arr) {
    arrList<T> *arr_result;
    arr_result = new arrList(maxSize);
    int pos1 = 0;
    int pos2 = 0;
    while (pos1 < len && pos2 < arr->length()) {
        T value1, value2;
        value1 = list[pos1];
        arr->getValue(pos2, value2);
        if (value1 == value2) {
            arr_result->append(value1);
            pos1++;
            pos2++;
        } else if (value1 > value2) pos2++;
        else pos1++;
    }
    return arr_result;
}

template<class T>
bool arrList<T>::getValue(const int pos, T &value) {
    if (pos >= len) {
        cout << "illegal position" << endl;
        return false;
    }
    value = list[pos];
    return true;
}

template<class T>
void arrList<T>::print() {
    if (len == 0) {
        cout << "None" << endl;
        return;
    }
    for (int i = 0; i < len; i++) {
        cout << list[i] << ' ';
    }
    cout << endl;
}

int main() {
    int arr1[] = {0, 3, 45, 2, 4};
    arrList<int> *arr_A;
    arr_A = new arrList<int>(arr1, (int) sizeof(arr1) / sizeof(*arr1), 100);
    arr_A->print();
    int arr2[] = {0, 3, 45, 2, 5};
    arrList<int> *arr_B;
    arr_B = new arrList<int>(arr2, (int) sizeof(arr2) / sizeof(*arr2), 100);
    arr_B->print();
    arrList<int> *arr_C = arr_A->intersection(arr_B);
    arr_C->print();
    return 0;
}
