#include <pthread.h>
#include <stdio.h>

void* inc_to_million(void *vp) {

    int *pi = (int*)vp;

    while (++*pi < 1000000);

    puts("increment finished!");

    return NULL;
}


int main() {
    int x = 0;
    int y = 1000000;
    pthread_t increment_thread;

    pthread_create(&increment_thread, NULL, inc_to_million, &x);

    while (--y > 0);

    puts("decrement finished!");

    pthread_join(increment_thread, NULL);

    printf("x: %d, y: %d\n", x,y);

}

