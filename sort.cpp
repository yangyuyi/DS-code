#include <iostream>
#include <queue>

using namespace std;

template<class Record>
void heap_sort(Record Array[], int n) {
    priority_queue<Record> max_heap;
    for (int i = 0; i < n; i++) max_heap.push(Array[i]);
    for (int i = n - 1; i >= 0; i--) {
        Array[i] = max_heap.top();
        max_heap.pop();
    }
}

template<class Record>
void quick_sort(Record *Array, int left, int right) {
    Record mid = Array[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while (Array[i] < mid) i++;
        while (Array[j] > mid) j--;
        if (i <= j) {
            Record tmp = Array[i];
            Array[i] = Array[j];
            Array[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > left) quick_sort(Array, left, j);
    if (i < right) quick_sort(Array, i, right);
}

class node {
public:
    int key;
    int nxt;
};

class static_queue {
public:
    int head;
    int tail;
};

template<class Record>
void radix_sort(Record *Array, int n, int d, int r) {
    static_queue *queue = new static_queue[r];
    int first = 0;
    for (int i = 0; i < n; i++) Array[i].nxt = i + 1;
    Array[n - 1].nxt = -1;
    for (int i = 0; i < d; i++) {
        distribute(Array, first, i, r, queue);
        collect(Array, first, r, queue);
    }
    delete[]queue;
    addr_sort(Array, n, first);
}

template<class Record>
void distribute(Record *Array, int first, int i, int r, static_queue *queue) {
    int cur = first;
    for (int j = 0; j < r; j++) queue[j].head = -1;
    while (cur != -1) {
        int k = Array[cur].key;
        for (int t = 0; t < i; t++) k /= r;
        k %= r;
        if (queue[k].head == -1) queue[k].head = cur;
        else Array[queue[k].tail].nxt = cur;
        queue[k].tail = cur;
        cur = Array[cur].nxt;
    }
}

template<class Record>
void collect(Record *Array, int &first, int r, static_queue *queue) {
    int k = 0;
    while (queue[k].head == -1) k++;
    first = queue[k].head;
    int last = queue[k].tail;
    while (k < r - 1) {
        k++;
        while (k < r - 1 && queue[k].head == -1) k++;
        if (queue[k].head != -1) {
            Array[last].nxt = queue[k].head;
            last = queue[k].tail;
        }
    }
    Array[last].nxt = -1;
}

template<class Record>
void addr_sort(Record *Array, int n, int first) {
    int j = first;
    for (int i = 0; i < n - 1; i++) {
        Record temp = Array[j];
        Array[j] = Array[i];
        Array[i] = temp;
        Array[i].nxt = j;
        j = temp.nxt;
        while (j <= i) j = Array[j].nxt;
    }
}

int main() {
    cout << "五 18072021[42] 杨雨怡 上机题5" << endl;
    cout << "Function choose:0-heap_sort 1-quick_sort 2-radix_sort:";
    int opt = -1;
    cin >> opt;
    if (opt == 0) {
        cout << "Heap Sort" << endl;
        cout << "Please input length of sequence:";
        int n = 0;
        cin >> n;
        cout << "Please input the sequence:";
        int Arr[n];
        for (int i = 0; i < n; i++) cin >> Arr[i];
        heap_sort(Arr, n);
        cout << "sorted sequence:";
        for (int i = 0; i < n; i++) cout << Arr[i] << ' ';
        cout << endl;
    }

    if (opt == 1) {
        cout << "Quick Sort" << endl;
        cout << "Please input length of sequence:";
        int n = 0;
        cin >> n;
        cout << "Please input the sequence:";
        int Arr[n];
        for (int i = 0; i < n; i++) cin >> Arr[i];
        quick_sort(Arr, 0, n - 1);
        cout << "sorted sequence:";
        for (int i = 0; i < n; i++) cout << Arr[i] << ' ';
        cout << endl;
    }

    if (opt == 2) {
        cout << "Radix Sort" << endl;
        cout << "Please input number of sort key:";
        int d = 0;
        cin >> d;
        cout << "Please input radix:";
        int radix = 1;
        cin >> radix;
        int max = 1;
        for (int i = 0; i < d; i++) max *= radix;
        cout << "Please input length of sequence:";
        int n = 0;
        cin >> n;
        cout << "Please input the sequence:";
        node Arr[n];
        for (int i = 0; i < n; i++) {
            int key = 0;
            cin >> key;
            if (!(key >= 0 && key < max)) {
                cout << "Illegal input!" << endl;
                return 0;
            }
            Arr[i].key = key;
        }
        radix_sort(Arr, n, d, radix);
        cout << "sorted sequence:";
        for (int i = 0; i < n; i++) cout << Arr[i].key << ' ';
        cout << endl;
    }
    return 0;
}
