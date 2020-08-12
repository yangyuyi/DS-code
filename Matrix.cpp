#include <iostream>

using namespace std;
#define SIZE_N 3

int main() {

    int matrix_a[SIZE_N][SIZE_N] = {{1, 1, 1},
                                    {2, 2, 2},
                                    {3, 3, 3}};
    int matrix_b[SIZE_N][SIZE_N] = {{1, 2, 3},
                                    {4, 5, 6},
                                    {7, 8, 9}};
    int matrix_ans[SIZE_N][SIZE_N];

    for (int i = 0; i < SIZE_N; i++) {
        for (int j = 0; j < SIZE_N; j++) {
            int res = 0;
            for (int k = 0; k < SIZE_N; k++)
                res += matrix_a[i][k] * matrix_b[k][j];
            matrix_ans[i][j] = res;
        }
    }

    for (int i = 0; i < SIZE_N; i++) {
        for (int j = 0; j < SIZE_N; j++) {
            cout << matrix_ans[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
