#include <pthread.h>
#include <stdio.h>

void *inc(void *x) {
    int *pi = (int *) x;
    *pi += 1;
    pthread_exit(NULL);
}

void *print_x(void *x) {
    printf("x: %d\n", (*(int*)x));
    pthread_exit(NULL);
}

// A simple data race which shows the non-determinism of threads. Sometimes the print thread will execute
// first, and x: 0 will print. Sometimes it will execute last, and x: 3 will print. It can also execute at any
// point in between increments. Sometimes the print statement won't execute at all! Why? 
// Try running it for yourself a couple times and see what results you get.
int main() {
    int x = 0;
    pthread_t inc1, inc2, inc3, print_thread;

    pthread_create(&inc1, NULL, inc, &x);
    pthread_create(&inc2, NULL, inc, &x);
    pthread_create(&inc3, NULL, inc, &x);
    pthread_create(&print_thread, NULL, print_x, &x);
    pthread_join(inc1, NULL);
    pthread_join(inc2, NULL);
    pthread_join(inc3, NULL);
    pthread_join(print_thread, NULL);
    return 0;
}
