#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#define N 4   // Tamaño matriz cuadrada

using namespace std;

int A[N][N];    // Matriz
int x[N];       // Vector
int y[N];       // Resultado

// Cada hilo calcula una fila de la multiplicación
void* multiplyRow(void* arg) {
    int row = (long)arg;
    y[row] = 0;
    for (int j = 0; j < N; j++) {
        y[row] += A[row][j] * x[j];
    }
    return NULL;
}

int main() {
    clock_t start = clock();
    srand(time(nullptr));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
        x[i] = rand() % 10;
    }

    pthread_t hilo[N];

    // Crea hilosxfila
    for (int i = 0; i < N; i++) {
        pthread_create(&hilo[i], NULL, multiplyRow, (void*)(long)i);
    }

    // termina hilos
    for (int i = 0; i < N; i++) {
        pthread_join(hilo[i], NULL);
    }

    cout << "\nMatriz A:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nVector x:\n";
    for (int i = 0; i < N; i++) {
        cout << x[i] << " ";
    }
    cout << "\n";

    cout << "\nResultado y = A * x:\n";
    for (int i = 0; i < N; i++) {
        cout << y[i] << " ";
    }
    cout << "\n";

    clock_t end = clock();
    double cpu_time = double(end - start) / CLOCKS_PER_SEC;
    cout << "\nTiempo CPU: " << cpu_time << " segundos\n";

    return 0;
}
