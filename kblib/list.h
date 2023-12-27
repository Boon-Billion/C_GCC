typedef struct node{
    void* data;
    int* priority;
    struct node* next;
    struct node* previous;
}list_s, *list_t;

list_t list_new();
list_t list_push(list_t list, int data);
list_t list_pop(list_t list);
int list_count(list_t list);

typedef struct{
    list_t head;
    list_t tail;
    int size;
}queue_s, *queue_t;

queue_t queue_new();

int enqueue(queue_t queue, void* value);
int dequeue(queue_t queue);
int size_queue(queue_t queue);
int enqueue_p(queue_t queue, void* value, int* priority);
void* dequeue_p(queue_t queue);