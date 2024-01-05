// #include <stdio.h>
// #include <stdlib.h>

// typedef struct{
//     size_t size;
//     size_t cap;
//     size_t* array;
// }max_heap_s, *max_heap_t;

// max_heap_t max_heap_new(){
//     max_heap_s proto = {0, 4, malloc(4 * sizeof(size_t))};
//     max_heap_t d = malloc(sizeof(max_heap_s));
//     *d = proto;
//     return d;
// }

// void max_heap_add(max_heap_t heap, size_t value){
//     if(heap->cap == heap->size){
//         heap->array = realloc(heap->array, heap->cap * 2 * sizeof(size_t));
//     }
//     heap->array[heap->size] = value;
//     size_t n = heap->size;
//     while(n >= 0){
//         if(heap->array[n] >= heap->array[(n-1)/2]){
//             size_t temp = heap->array[n];
//             heap->array[n] = heap->array[(n-1)/2];
//             heap->array[(n-1)/2] = temp;
//         }
//     }
//     heap->size++;
// }
