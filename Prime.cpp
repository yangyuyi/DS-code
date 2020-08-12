#include <iostream>

#define MAXN 100000000
#define N 100000

using namespace std;
int prime[MAXN];
bool vis[MAXN];

int Prime(int n) {
    int cnt = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < n; i++) {
        if (!vis[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && i * prime[j] < n; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    return cnt;
}

int main() {
    int cnt = Prime(N);
    for (int i = 0; i < cnt; i++) cout << prime[i] << ' ';
    return 0;
}
