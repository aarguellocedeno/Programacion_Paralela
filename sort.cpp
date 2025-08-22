#include <stdio.h>

#define MAX 100 

void Count_sort(int a[], int n) {
    int temp[MAX];
    int i, j, count;

    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++) {
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        }
        temp[count] = a[i];
    }

    // se actualiza en el a
    for (i = 0; i < n; i++) {
        a[i] = temp[i];
    }
}

int main() {
    int a[MAX], n;

    printf("Ingrese el tamaño del arreglo (máx %d): ", MAX);
    scanf("%d", &n);

    printf("Ingrese %d elementos:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    Count_sort(a, n);

    printf("Arreglo ordenado:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}
