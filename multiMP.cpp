#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#define N 4

int A[N][N],B[N][N],C[N][N];

int main() {
    srand(time(nullptr));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    #pragma omp parallel
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int local_sum=0;
            for (int k = 0; k < N; k++) {
                local_sum += A[i][k] * B[k][j];
            }
            C[i][j] = local_sum;
        }
    }

    cout << "\nMatriz (A x B):\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
