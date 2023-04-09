#include <stdio.h>
#include <pthread.h>
#include "list.h"

void* insert_values(void* args) {
    struct linked_list *ll = (struct linked_list*)args;

    // Insert values into linked list
    for (int i = 1; i <= 1000; i++) {
        ll_add(ll, i);
    }

    pthread_exit(NULL);
}

void* lookup_values(void* args) {
    struct linked_list *ll = (struct linked_list*)args;

    // Look up values in linked list
    for (int i = 1; i <= 1000; i++) {
        ll_contains(ll, i);
    }

    pthread_exit(NULL);
}

void* remove_values(void* args) {
    struct linked_list *ll = (struct linked_list*)args;

    // Remove values from linked list
    for (int i = 1; i <= 500; i++) {
        ll_remove_first(ll);
    }

    pthread_exit(NULL);
}

int main() {
    // Create linked list and initialize pthreads
    struct linked_list *ll = ll_create();
    pthread_t threads[3];

    // Create threads for insertion, lookup, and removal
    pthread_create(&threads[0], NULL, insert_values, (void*)ll);
    pthread_create(&threads[1], NULL, lookup_values, (void*)ll);
    pthread_create(&threads[2], NULL, remove_values, (void*)ll);

    // Wait for threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    // Check final contents of linked list
    display(ll);

    // Destroy linked list and exit
    ll_destroy(ll);
    return 0;
}

