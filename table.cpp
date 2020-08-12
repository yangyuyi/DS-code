#include<iostream>
#include<cmath>

using namespace std;
#define MAX_N 100

int rec[9];
bool vis[MAX_N];
int n = 10;

bool isPrime(int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) return false;
    }
    return true;
}

bool check(int arr[]) {
    return isPrime(arr[0] + arr[1]) &&
           isPrime(arr[1] + arr[2]) &&
           isPrime(arr[3] + arr[4]) &&
           isPrime(arr[4] + arr[5]) &&
           isPrime(arr[6] + arr[7]) &&
           isPrime(arr[7] + arr[8]) &&
           isPrime(arr[0] + arr[3]) &&
           isPrime(arr[1] + arr[4]) &&
           isPrime(arr[2] + arr[5]) &&
           isPrime(arr[3] + arr[6]) &&
           isPrime(arr[4] + arr[7]) &&
           isPrime(arr[5] + arr[8]);
}

void dfs(int dep) {
    if (dep == 9) {
        if (check(rec)) {
            for (int i = 0; i < 9; i++) {
                cout << rec[i] << ' ';
                if (i % 3 == 2) cout << '\n';
            }
            cout << '\n';
        }
    } else {
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                rec[dep] = i;
                vis[i] = true;
                dfs(dep + 1);
                vis[i] = false;
            }
        }
    }
}


int main() {
    dfs(0);
    return 0;
}