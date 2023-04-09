#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include <pthread.h> // Include pthread library for locks

struct node{
    int data;
    struct node *next;
};

struct linked_list{
    struct node *head;
    int length;

    pthread_mutex_t lock; // Declare lock for linked list
};

static inline struct linked_list *
ll_create(void)
{
    struct linked_list *ll = malloc(sizeof(struct linked_list));
    ll -> length = 0;
    ll -> head = NULL;
    pthread_mutex_init(&ll->lock, NULL); // Initialize lock

    if(ll == NULL){
        return NULL;
    }
    return ll;
}

static inline int
ll_destroy(struct linked_list *ll)
{
    if(ll-> length){ // checks if ll is not empty
        return 0;
    }else{
        pthread_mutex_destroy(&ll->lock); // Destroy lock before freeing memory
        free(ll);
        ll = NULL;
        return 1;
    }
}

static inline void
ll_add(struct linked_list *ll, int value)
{
    pthread_mutex_lock(&ll->lock); // Lock critical section
    struct node *temp = malloc(sizeof(struct node));
    assert(temp != NULL);
    temp -> data = value;
    temp -> next = ll -> head;
    ll -> head = temp;
    ll -> length++;
    pthread_mutex_unlock(&ll->lock); // Unlock critical section
}

static inline int
ll_length(struct linked_list *ll)
{
    return ll -> length;
}

static inline bool
ll_remove_first(struct linked_list *ll)
{
    pthread_mutex_lock(&ll->lock); // Lock critical section
    if(ll -> length){
        struct node *temp = ll -> head;
        ll -> head = ll -> head -> next;
        free(temp);
        ll -> length--;
        pthread_mutex_unlock(&ll->lock); // Unlock critical section
        return true;
    }
    pthread_mutex_unlock(&ll->lock); // Unlock critical section
    return false;
}

static inline int
ll_contains(struct linked_list *ll, int value)
{
    pthread_mutex_lock(&ll->lock); // Lock critical section
    bool nodefound = false;
    struct node *temp = ll -> head;
    int placement = 1;
    while(temp != NULL && nodefound == false){
        if(temp -> data == value){
            nodefound = true;
        }else{
            temp = temp -> next;
            placement++;
        }
    }
    pthread_mutex_unlock(&ll->lock); // Unlock critical section

    if(nodefound){
        return placement;
    }
    return 0;
}

void display(struct linked_list *ll)
{
    struct node *temp = ll -> head;
    if(temp == NULL){
        printf("\nL_List is empty");
    }
    while(temp != NULL){
        printf("\t%d", temp -> data);
    }
}

#endif /* LIST_H_ */

