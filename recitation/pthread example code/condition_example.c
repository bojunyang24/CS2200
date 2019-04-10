#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define MAX_SIZE 5

uint32_t size = 0;

pthread_mutex_t buf_mutex;
pthread_cond_t buf_not_empty, buf_not_full;

void *add_to_buf(void *foo) {
    puts("add thread starting!");
    sleep(1);
    pthread_mutex_lock(&buf_mutex);
    puts("add thread locked!");
    while (size == MAX_SIZE) {
        pthread_cond_wait(&buf_not_full, &buf_mutex);
    }
    size++;
    pthread_mutex_unlock(&buf_mutex);
    pthread_cond_broadcast(&buf_not_empty);
    return NULL;
}

void *remove_from_buf(void *foo) {
    puts("remove thread starting!");
    pthread_mutex_lock(&buf_mutex);
    puts("remove thread locked!");
    while (size == 0) {
        pthread_cond_wait(&buf_not_empty, &buf_mutex);
    }
    size--;
    pthread_mutex_unlock(&buf_mutex);
    pthread_cond_broadcast(&buf_not_full);
    return NULL;
}

int main()
{
    puts("starting!");
    pthread_t producer, consumer;

    pthread_mutex_init(&buf_mutex, NULL);
    pthread_cond_init(&buf_not_empty, NULL);
    pthread_cond_init(&buf_not_full, NULL);

    pthread_create(&consumer, NULL, remove_from_buf, NULL);
    pthread_create(&producer, NULL, add_to_buf, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    puts("done!");
}
