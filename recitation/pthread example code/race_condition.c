#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct list {
    int data;
    struct list *next;
} list_t;

list_t *cool_list;
pthread_mutex_t list_mutex;


void print_list() {
    list_t *curr = cool_list;

    while (curr) {
        if (curr->next) {
            printf("%d -> ", curr->data);
        } else {
            printf("%d\n", curr->data);
        }
        curr = curr->next;
    }
}

// What's wrong with this?
void insert(int data) {
    list_t *new;
    new = malloc(sizeof(list_t));
    new->data = data;
    new->next = cool_list;
    cool_list = new;
}

void *thread_add_three_sleep(void *foo) {
    pthread_mutex_lock(&list_mutex);
    usleep(1);
    insert(5);
    insert(10);
    insert(15);
    //puts("sleep done");
    pthread_mutex_unlock(&list_mutex);
    pthread_exit(NULL);
}
void *thread_add_three(void *foo) {
    pthread_mutex_lock(&list_mutex);
    insert(5);
    insert(10);
    insert(15);
    //puts("regular done");
    pthread_mutex_unlock(&list_mutex);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    // insert(1);
    // insert(2);
    // insert(3);
    // print_list();

    pthread_t lt1, lt2, lt3;

    // Uh-oh...
    pthread_create(&lt1, NULL, thread_add_three_sleep, NULL);
    pthread_create(&lt2, NULL, thread_add_three, NULL);
    pthread_create(&lt3, NULL, thread_add_three, NULL);

    // Wait for the child threads to finish
    pthread_join(lt1, NULL);
    pthread_join(lt2, NULL);
    pthread_join(lt3, NULL);

    print_list();
}
