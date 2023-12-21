
#define MAX_DICT INT_MAX
typedef struct{
    const char* key;
    long long value;
}dict_entry_s;

typedef struct{
    size_t len;
    size_t cap;
    dict_entry_s* entry;
}dict_s, *dict_t;

dict_t dict_new(void);
long long dict_find(dict_t dict, const char *key, int def);
int dict_add(dict_t dict, const char *key, long long value);
int dict_remove(dict_t dict, const char *key);
void dict_free(dict_t dict);
