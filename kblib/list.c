#include<list.h>
#include<stdlib.h>
#include<stdio.h>

//TODO LIST_FREE, QUEUE_FREE, PRIORITY_QUEUE

list_t list_new(){
    list_t list = 0;
    return list;
}

list_t list_push(list_t list, int data){
    list_t new_list = malloc(sizeof(list_s));
    new_list->data = data;
    new_list->next = list;
    new_list->previous = 0;
    if(list){
        list->previous = new_list;
    }
    return new_list;
}

list_t list_pop(list_t list){
    if(list == 0){
        fprintf(stderr, "List Empty\n");
        exit(EXIT_FAILURE);
    }
    list_t next_list = list->next;
    if(next_list == 0){
        free(list);
        return 0;
    }
    list->next->previous = 0;
    free(list);
    return next_list;
}

int list_count(list_t list){
    int count = 0;
    if(!list){
        return 0;
    }
    while(list->next){
        list = list->next;
        count++;
    }
    return count + 1;
}

queue_t queue_new(){
    queue_s proto = {0, 0};
    queue_t queue = malloc(sizeof(queue_s));
    *queue = proto;
    return queue;
}

int enqueue(queue_t queue, int value){   
    if(queue->head == 0){
        list_t new_list = malloc(sizeof(list_s));
        new_list->data = value;
        new_list->next = 0;
        new_list->previous = 0;
        queue->head = new_list;
        queue->tail = new_list;
    }
    else{
        list_t new_list = malloc(sizeof(list_s));
        new_list->data = value;
        new_list->next = 0;
        new_list->previous = queue->tail;
        queue->tail->next = new_list;
        queue->tail = new_list;
    }
    queue->size++;
}

int dequeue(queue_t queue){
    if(queue->size == 0){
        fprintf(stderr, "Queue Empty\n");
        exit(EXIT_FAILURE);
    }
    int value = queue->head->data;  
    list_t next_list = queue->head->next;
    list_pop(queue->head);
    
    queue->head = next_list;
    if(next_list == 0){
        queue->tail = 0;
    }
    queue->size--;
    return value;
}

int size_queue(queue_t queue){
    return queue->size;
}