#include<list.h>
#include<stdlib.h>
#include<stdio.h>

//TODO LIST_FREE, QUEUE_FREE

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

int enqueue(queue_t queue, void* value){   
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

int enqueue_p(queue_t queue, void* value, int priority){  
    list_t new_list = malloc(sizeof(list_s));
    new_list->data = value;
    new_list->priority = priority;
    new_list->next = 0; 

    if(queue->head == 0){
        new_list->previous = 0;
        queue->head = new_list;
        queue->tail = new_list;
    }
    else{
        new_list->previous = queue->tail;
        queue->tail->next = new_list;
        queue->tail = new_list;
    }
    queue->size++;
}

void* dequeue_p(queue_t queue){
    if(queue->size == 0){
        fprintf(stderr, "Queue Empty\n");
        exit(EXIT_FAILURE);
    }
    
    list_t list = queue->head;
    list_t highest_priority = list;
    for(int i = 0; i < queue->size; i++){
        if(queue->size == 1){
            highest_priority = list;
            break;
        }
        if(highest_priority->priority > list->priority){
            highest_priority = list;
        }
        list = list->next;
    }
    void* value = highest_priority->data;

    if(highest_priority->previous == 0 && highest_priority->next == 0){
        queue->head = 0;
        queue->tail = 0;
    }
    else if(highest_priority->previous == 0){
        queue->head = highest_priority->next;
        highest_priority->next->previous = 0;
    }
    else if(highest_priority->next == 0){
        queue->tail = highest_priority->previous;
        highest_priority->previous->next = 0;        
    }
    else{
        highest_priority->previous->next = highest_priority->next;
        highest_priority->next->previous = highest_priority->previous;
    }
    queue->size--;
    free(highest_priority);
    return value;
}
