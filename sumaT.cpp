#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
using namespace std;

#define N 100000000
int arr[N];
int res1,res2;

void *arrw(){
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        arr[i] = rand() % 10;
    }
    printf("\n");
    return NULL;
}

void *suma1(void *uno){
    res1=0;
    for(int i=0;i<(N/2);i++){
        res1 += arr[i];
    }
    return NULL;
}

void *suma2(void *dos){
    res2=0;
    for(int i=(N/2);i<N;i++){
        res2 += arr[i];
    }
    return NULL;
}


int main(){
    arrw();
    for (int i =0; i <  N; i++){
        cout << arr[i] << " ";
    }
    pthread_t t1, t2;
    pthread_create(&t1, NULL, suma1, NULL);
    pthread_create(&t2, NULL, suma2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    int total = res1 + res2;
    cout << "resultado = "<< total <<endl;
    return 0;
}


