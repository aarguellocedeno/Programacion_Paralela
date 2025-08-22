#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Trap(double a, double b, int n, double* global_result_p) {
    double h, x, ans;
    double local_a, local_b;
    int i, local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b - a) / n;
    local_n = n / thread_count;
    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;

    // Aquí en vez de f(x) usamos directamente x*x
    ans = (local_a*local_a + local_b*local_b) / 2.0;
    for (i = 1; i <= local_n - 1; i++) {
        x = local_a + i * h;
        ans += x * x;   // f(x) = x^2
    }
    ans *= h;

    #pragma omp critical
    *global_result_p += ans;
}

int main(int argc, char* argv[]) {
    double global_result = 0.0;
    double a, b;
    int n, thread_count;

    thread_count = strtol(argv[1], NULL, 10);

    printf("Ingrese a, b y n:\n");
    scanf("%lf %lf %d", &a, &b, &n);

    #pragma omp parallel num_threads(thread_count)
    Trap(a, b, n, &global_result);

    printf("Con n = %d trapecios, la integral de %f a %f = %.14e\n",
           n, a, b, global_result);

    return 0;
}
