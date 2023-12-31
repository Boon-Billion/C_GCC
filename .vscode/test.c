
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
}max_heap_s, *max_heap_t;

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

void* max_heap_pop(max_heap_t heap){
    if(heap->size == 0){
        return 0;
    }
    void* temp = heap->node[0].data;
    if(heap->size == 1){
        heap->size--;
        heap->node[0].data = 0;
        return temp;
    }
    heap->size--;
    heap->node[0].data = heap->node[heap->size].data;
    heap->node[0].priority = heap->node[heap->size].priority;
    heap->node[heap->size].data = 0;

    long long n = 0;
    while (n <= heap->size){
        if(heap->node[n].priority >= heap->node[(n*2)+1].priority && heap->node[n].priority >= heap->node[(n*2)+2].priority){
            break;
        }
        else if(heap->node[n].priority < heap->node[(n*2)+1].priority){
            long long temp = heap->node[n].priority;
            void* data_temp = heap->node[n].data;

            heap->node[n].priority = heap->node[(n*2)+1].priority;
            heap->node[n].data = heap->node[(n*2)+1].data;
            heap->node[(n*2)+1].priority = temp;
            heap->node[(n*2)+1].data = data_temp;
            n = (n * 2) + 1;
        }
        else if (heap->node[n].priority < heap->node[(n*2)+2].priority){
            if((n*2)+2 > heap->size){
                break;
            }
            long long temp = heap->node[n].priority;
            void* data_temp = heap->node[n].data;

            heap->node[n].priority = heap->node[(n*2)+2].priority;
            heap->node[n].data = heap->node[(n*2)+2].data;
            heap->node[(n*2)+2].priority = temp;
            heap->node[(n*2)+2].data = data_temp;
            n = (n * 2) + 2;
        }
        
    }
    return temp;

    
}

int main(){
    max_heap_t test = max_heap_new();
    max_heap_add(test, "test35", 35);
    max_heap_add(test, "test33", 33);
    max_heap_add(test, "test42", 42);
    max_heap_add(test, "test10", 10);
    max_heap_add(test, "test14", 14);
    max_heap_add(test, "test19", 19);
    max_heap_add(test, "test27", 27);
    max_heap_add(test, "test44", 44);
    max_heap_add(test, "test26", 26);
    max_heap_add(test, "test31", 31);

    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    printf("%s\n", max_heap_pop(test));
    return 0;
}