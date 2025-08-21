#include <iostream>
#include <vector>
#include <cstdlib>  
#include <omp.h> 
using namespace std; 

int main(){
    const long N = 100000000; 
    long arr[N];

    for(long i = 0; i < N; i++){
        arr[i] = rand() % 10; 
    }
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(long i = 0; i < N; i++){
        sum += arr[i];
    }

    cout << "Suma total = " << sum << "\n";
    return 0;
}
