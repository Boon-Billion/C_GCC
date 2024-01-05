typedef struct list_entry list_entry_s, *list_entry_t;
typedef struct list list_s, *list_t;

list_t list_new(void);
list_t list_push(list_t list, void* addr);
void* list_get_top(list_t list);
unsigned long long list_size(list_t list);
void* list_pop(list_t list);
void list_free(list_t list);