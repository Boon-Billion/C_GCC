#include<list.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct list_entry{
    void* data;
    struct list_entry* next;
    struct list_entry* previous;
}list_entry_s, *list_entry_t;

typedef struct list{
    size_t size;
    size_t cap;
    list_entry_s* node;
}list_s, *list_t;

list_t list_new(void){
    list_s proto = {0, 4, malloc(4 * sizeof(list_entry_s))};
    list_t d = malloc(sizeof(list_s));
    *d = proto;
    return d;
}

list_t list_push(list_t list, void* addr){
    if(list->cap == list->size){
        list->cap *= 2;
        list->node = realloc(list->node, list->cap * 2 * sizeof(list_entry_s));
    }
    list_entry_s proto = {addr, 0, 0};
    list_entry_t node = malloc(sizeof(list_entry_s));
    *node = proto;
    if(list->size > 0){
        list->node->previous = node;
        node->next = list->node;     
    }
    list->node = node;
    list->size++;
}

void* list_pop(list_t list){
    if(list->size == 0){
        return 0;
    }
    void* d = list->node->data;
    list->size--;
    list_entry_t temp = 0;
    if(list->size > 0){
        temp = list->node->next;
        temp->previous = 0;    
    }
    free(list->node);
    list->node = temp; 
    return d;
}

void list_free(list_t list){
    for(int i = 0; i < list->size; i++){
        list_pop(list);
    }
    free(list);
}

void* list_get_top(list_t list){
    if(list->size == 0){
        return 0;
    }
    return list->node->data;
}

size_t list_size(list_t list){
    return list->size;
}


