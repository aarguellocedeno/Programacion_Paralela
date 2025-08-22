#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <cstdlib>
using namespace std;

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t emptySlots;  
sem_t fullSlots;   
pthread_mutex_t mutex;

void* productor(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100;  

        sem_wait(&emptySlots);       
        pthread_mutex_lock(&mutex);  
        buffer[in] = item;
        cout << "Productor produjo: " << item << endl;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&fullSlots);         
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&fullSlots);    
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        cout << "Consumidor consumió: " << item << endl;
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);  
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t prod, cons;

    // inicializar semáforos y mutex
    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // crear hilos
    pthread_create(&prod, NULL, productor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);

    // esperar que terminen
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // limpiar
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
