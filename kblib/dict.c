#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

dict_t dict_new(void){
    dict_s proto = {0, 4, malloc(4 * sizeof(dict_entry_s))};
    dict_t d = malloc(sizeof(dict_s));
    *d = proto;
    return d;
}

long long _dict_find_index(dict_t dict, const char *key) {
    for (long long i = 0; i < dict->len; i++) {
        if (!strcmp(dict->entry[i].key, key)) {
            return i;
        }
    }
    return -1;
}

long long dict_find(dict_t dict, const char *key, int def) {
    size_t idx = _dict_find_index(dict, key);
    return idx == -1 ? def : dict->entry[idx].value;
}

int dict_add(dict_t dict, const char *key, long long value) {
   long long idx = _dict_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value = value;
       return 2;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
        if(dict->cap >= MAX_DICT){
            return 0;
        }
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
   }
   dict->entry[dict->len].key = strdup(key);
   dict->entry[dict->len].value = value;
   dict->len++;
   return 1;
}

void dict_free(dict_t dict) {
    for (int i = 0; i < dict->len; i++) {
        free((void*)dict->entry[i].key);
    }
    free(dict->entry);
    free(dict);
}
