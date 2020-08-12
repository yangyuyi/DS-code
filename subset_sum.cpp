#include<iostream>
#include<cstring>


using namespace std;
#define MAXN 10000

int n, c;
int x[MAXN];
int vis[MAXN], rec[MAXN];
bool _find;

void print(int dep) {
    for (int i = 1; i <= dep; ++i)
        cout << rec[i] << ' ';
    cout << endl;
}

void search(int dep, int sum) {
    for (int r = 1; r <= n; ++r)
        if (!vis[r] && sum - x[r] >= 0) {
            rec[dep] = x[r];
            vis[r] = 1;
            if (sum == x[r]) {
                print(dep);
                _find = 1;
                return;
            } else search(dep + 1, sum - x[r]);
            if (_find == 1) return;
            else vis[r] = 0;
        }
}

int main() {
    cin >> n >> c;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
        sum += x[i];
    }

    if (sum < c) {
        cout << "No solution!";
        return 0;
    }

    memset(rec, 0, sizeof(rec));
    memset(vis, 0, sizeof(vis));

    _find = 0;
    search(1, c);
    if (!_find) cout << "No solution!" << endl;
    return 0;
}