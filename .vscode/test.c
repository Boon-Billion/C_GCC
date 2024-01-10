
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    void* data;
    long long priority;
}node_s, *node_t;

typedef struct{
    size_t size;
    size_t cap;
    node_s* node;
}max_heap_s, *max_heap_t, min_heap_s, *min_heap_t;

max_heap_t max_heap_new(){
    max_heap_s proto = {0, 4, malloc(4 * sizeof(node_s))};
    max_heap_t d = malloc(sizeof(max_heap_s));
    *d = proto;
    return d;
}

void max_heap_add(max_heap_t heap, void* data, long long priority){
    if(heap->cap == heap->size){
        heap->cap *= 2;
        heap->node = realloc(heap->node, heap->cap * sizeof(node_s));
    }
    heap->node[heap->size].priority = priority;
    heap->node[heap->size].data = data;
    long long n = heap->size;
    heap->size++;
    while(n > 0){
        if(heap->node[n].priority <= heap->node[(n-1)/2].priority){
            break;
        }
        long long temp = heap->node[n].priority;
        void* data_temp = heap->node[n].data;

        heap->node[n].priority = heap->node[(n-1)/2].priority;
        heap->node[n].data = heap->node[(n-1)/2].data;
        heap->node[(n-1)/2].priority = temp;
        heap->node[(n-1)/2].data = data_temp;
        n = (n-1)/2;    
    }
    
}
void heap_swap(max_heap_t heap, size_t a, size_t b){
    void* current_node = heap->node[a].data;
    size_t current_priority = heap->node[a].priority;
    heap->node[a].data = heap->node[b].data;
    heap->node[a].priority = heap->node[b].priority;
    heap->node[b].data = current_node;
    heap->node[b].priority = current_priority;
}
void* max_heap_pop(max_heap_t heap){
    if(heap->size == 0){
        return 0;
    }
    // n = (n * 2) + 1;
    void* temp = heap->node[0].data;
    heap->node[0] = heap->node[heap->size - 1];
    heap->size--;

    long long ln = 0;
    long long rn = 0;
    size_t current_node_index = 0;
    
    do{    
        ln = (current_node_index * 2) + 1;
        rn = ln + 1;
        if(ln >= heap->size){
            break;
        }
        if(heap->node[current_node_index].priority < heap->node[ln].priority && rn >= heap->size){
            heap_swap(heap, current_node_index, ln);
            current_node_index = ln;
        }
        else if(heap->node[current_node_index].priority < heap->node[ln].priority && heap->node[ln].priority > heap->node[rn].priority && rn < heap->size){
            heap_swap(heap, current_node_index, ln);
            current_node_index = ln;

        }
        else if(heap->node[current_node_index].priority < heap->node[rn].priority && heap->node[rn].priority > heap->node[ln].priority && rn < heap->size){
            heap_swap(heap, current_node_index, rn);
            current_node_index = rn;
        }
        else{
            break;
        }
    } 
    while (current_node_index < heap->size);
    return temp;
}

min_heap_t min_heap_new(){
    min_heap_s proto = {0, 4, malloc(4 * sizeof(node_s))};
    min_heap_t d = malloc(sizeof(min_heap_s));
    *d = proto;
    return d;
}

void min_heap_add(min_heap_t heap, void* data, long long priority){
    if(heap->cap == heap->size){
        heap->cap *= 2;
        heap->node = realloc(heap->node, heap->cap * sizeof(node_s));
    }
    heap->node[heap->size].priority = priority;
    heap->node[heap->size].data = data;
    long long n = heap->size;
    heap->size++;
    while(n > 0){
        if(heap->node[n].priority >= heap->node[(n-1)/2].priority){
            break;
        }
        long long temp = heap->node[n].priority;
        void* data_temp = heap->node[n].data;

        heap->node[n].priority = heap->node[(n-1)/2].priority;
        heap->node[n].data = heap->node[(n-1)/2].data;
        heap->node[(n-1)/2].priority = temp;
        heap->node[(n-1)/2].data = data_temp;
        n = (n-1)/2;    
    }
    
}

void* min_heap_pop(min_heap_t heap){
    if(heap->size == 0){
        return 0;
    }
    // n = (n * 2) + 1;
    void* temp = heap->node[0].data;
    heap->node[0] = heap->node[heap->size - 1];
    heap->size--;

    long long ln = 0;
    long long rn = 0;
    size_t current_node_index = 0;
    
    do{    
        ln = (current_node_index * 2) + 1;
        rn = ln + 1;
        if(ln >= heap->size){
            break;
        }
        if(heap->node[current_node_index].priority > heap->node[ln].priority && rn >= heap->size){
            heap_swap(heap, current_node_index, ln);
            current_node_index = ln;
        }
        else if(heap->node[current_node_index].priority > heap->node[ln].priority && heap->node[ln].priority < heap->node[rn].priority && rn < heap->size){
            heap_swap(heap, current_node_index, ln);
            current_node_index = ln;

        }
        else if(heap->node[current_node_index].priority > heap->node[rn].priority && heap->node[rn].priority < heap->node[ln].priority && rn < heap->size){
            heap_swap(heap, current_node_index, rn);
            current_node_index = rn;
        }
        else{
            break;
        }
    } 
    while (current_node_index < heap->size);
    return temp;



    
}

int main(){
    min_heap_t test = min_heap_new();
    min_heap_add(test, "test35", 35);
    min_heap_add(test, "test33", 33);
    min_heap_add(test, "test42", 42);
    min_heap_add(test, "test10", 10);
    min_heap_add(test, "test14", 14);
    min_heap_add(test, "test19", 19);
    min_heap_add(test, "test27", 27);
    min_heap_add(test, "test44", 44);
    min_heap_add(test, "test26", 26);
    min_heap_add(test, "test31", 31);

    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    printf("%s\n", min_heap_pop(test));
    return 0;
}