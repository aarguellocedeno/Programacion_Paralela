
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

#define N = 4; 

int A[N][N],B[N][N], C[N][N];


void* multiplyRow(void* arg) {
    int row = (long)arg;   

    for(int j = 0; j < N; j++) {
        C[row][j] = 0;
        for(int k = 0; k < N; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
    return NULL;
}

int main() {
    srand(time(nullptr));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    pthread_t hilo[N];

    // un hiloxfila
    for(int i = 0; i < N; i++) {
        pthread_create(&hilo[i], NULL, multiplyRow, (void*)(long)i);
    }

    for(int i = 0; i < N; i++) {
        pthread_join(hilo[i], NULL);
    }

    cout << "\nMatriz Resultado (A x B):\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
