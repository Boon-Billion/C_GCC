#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void get_hash(char* buffer, int hash_len, int padding_len);
int shift_left(char* str);
int check_valid(char* chunk, char* spring);
int shift_right(char* str);
int append_spring(char* padded_spring, char* spring_record);
typedef struct{
    const char* key;
    long long value;
}dict_entry_s;

typedef struct{
    int len;
    int cap;
    dict_entry_s* entry;
}dict_s, *dict_t;
long long dfs(char* padded_string, int* record_arr, int index, dict_t memo);
int get_hash_count(char* spring);
long long all_posible_count = 0;



dict_t create_dict(void);
int dict_find_index(dict_t dict, const char *key);
long long dict_find(dict_t dict, const char *key, int def);
void dict_add(dict_t dict, const char *key, long long value);
void dict_free(dict_t dict);
FILE* file;
char string_buffer[1024] = { 0 };
int main(void) {
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    file = fopen("input.txt", "r");
    if (file == NULL) {
        return 1;
    }
    

    while (fgets(string_buffer, 1024, file)) {
        dict_t memo = create_dict();
        char* spring = 0;
        char* record = 0;
        spring = strtok_s(string_buffer, " ", &record);

        
        /////unfold/////
        int str_len = strlen(spring);
        char* unfold_part = (char*)malloc((str_len + 2) * sizeof(char));
        unfold_part[0] = '?';
        strcpy(unfold_part + 1, string_buffer);
        str_len = str_len + ((str_len + 1)*4);
        int padded_len = str_len + 3;
        char* padded_spring = (char*)malloc(padded_len * sizeof(char));
        padded_spring[0] = '.';
        char* str_temp = padded_spring+1;
        strcpy(str_temp, spring);
        for (int i = 0; i < 4; i++){
            strcat(padded_spring, unfold_part);
        }
        free(unfold_part);
        padded_spring[padded_len - 1] = 0;
        padded_spring[padded_len - 2] = '.';

        ///padding (padded_spring)////
        //int padded_len = strlen(spring) + 3;
        //char* padded_spring = (char*)malloc(padded_len * sizeof(char));
        // for (int i = 0; i < padded_len; i++) {
        //     if (i == 0) { padded_spring[i] = '.'; }
        //     else if (i == padded_len - 2) { padded_spring[i] = '.'; }
        //     else if (i == padded_len - 1) { padded_spring[i] = 0; }
        //     else { padded_spring[i] = spring[i - 1]; }
        // }
        // printf("\t%s  ", padded_spring);

        //record in integer (record_arr)
        int record_len = 0;
        char* record_token;
        int* record_arr = (int*)malloc(sizeof(int));
        record = strtok_s(record, ",", &record_token);

        while (record) {
            record_len++;
            record_arr = (int*)realloc(record_arr, record_len * sizeof(int));
            record_arr[record_len - 1] = atoi(record);
            record = strtok_s(NULL, ",", &record_token);
        }
        int temp = 0;
        temp = record_len;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < temp; j++){
                record_len++;
                record_arr = (int*)realloc(record_arr, record_len * sizeof(int));
                record_arr[record_len - 1] = record_arr[j];
            }
        }


        record_arr = (int*)realloc(record_arr, (record_len + 1) * sizeof(int));
        record_arr[record_len] = 0;

        //  for (int i = 0; i < record_len; i++) {
        //      printf("%d ", record_arr[i]);
        // }
        //printf("\n");
        long long check = 0;
        check = dfs(padded_spring, record_arr, 0, memo);        
        all_posible_count += check;
        //printf("\n\t %lld", all_posible_count);
        free(padded_spring);
        free(record_arr);
        dict_free(memo);
    }
    printf("\n\tPart2: %lld", all_posible_count);
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    printf("\n\tTime Elapsed: %f\n", timeElapsed);
    return 0;
}

long long dfs(char* padded_string, int* record_arr, int index, dict_t memo) {

    char str_record[8] = {0};
    char str_index[8] = {0};
    sprintf(str_record, ", %d, ", record_arr[index]);
    sprintf(str_index, "%d", index);
    int key_size = (strlen(padded_string) + strlen(str_record) + strlen(str_index) + 1) * sizeof(char);
    char* key = malloc(key_size);
    strcpy(key, padded_string);
    strcat(key, str_record);
    strcat(key, str_index);

    long long memo_check = dict_find(memo, key, -1);
    if(memo_check!=-1){
        free(key);
        return memo_check;
    }

    int hesh_count = 0;
    if (!record_arr[index]) {
        hesh_count = get_hash_count(padded_string);
        if (hesh_count) {
            return 0;
        }
        else {
            return 1;
        }
    }

    long long count = 0;
    int shift_count = 0;
    int record = record_arr[index];
    int padded_len = strlen(padded_string) + 1;
    char* padded_spring_copy = (char*)malloc(padded_len * sizeof(char));
    char* record_spring = (char*)malloc(padded_len * sizeof(char));

    get_hash(record_spring, record, padded_len);

    while (shift_left(record_spring)) {
        
        shift_count++;
        
        if (check_valid(record_spring, padded_string)) {
            strcpy(padded_spring_copy, padded_string);
            int cut_index = record + 1 + shift_count; //new space 9 + 1
            int new_len = padded_len - cut_index;
            padded_spring_copy[cut_index] = 0;
            append_spring(padded_spring_copy, record_spring);
            
            //padded_spring_copy[cut_index] = 0;

            if (get_hash_count(padded_spring_copy) == record) {          
                int temp = index + 1;
                int test = 0;
                int k = 1;
                for (int i = cut_index; i < new_len + cut_index; i++) {
                    if (i == new_len + cut_index - 1) {
                        padded_spring_copy[k++] = 0;
                    }
                    else {
                        padded_spring_copy[k++] = padded_string[i];
                    }
                }
                count += dfs(padded_spring_copy, record_arr, temp, memo);                    
            }        
        }   
    }

    dict_add(memo, key, count);
    free(key);
    free(padded_spring_copy);
    free(record_spring);
    
    return count;
}

dict_t create_dict(void){
    dict_s proto = {0, 10, malloc(10 * sizeof(dict_entry_s))};
    dict_t d = malloc(sizeof(dict_s));
    *d = proto;
    return d;
}

int dict_find_index(dict_t dict, const char *key) {
    for (int i = 0; i < dict->len; i++) {
        if (!strcmp(dict->entry[i].key, key)) {
            return i;
        }
    }
    return -1;
}

long long dict_find(dict_t dict, const char *key, int def) {
    int idx = dict_find_index(dict, key);
    return idx == -1 ? def : dict->entry[idx].value;
}

void dict_add(dict_t dict, const char *key, long long value) {
   long long idx = dict_find_index(dict, key);
   if (idx != -1) {
       dict->entry[idx].value = value;
       return;
   }
   if (dict->len == dict->cap) {
       dict->cap *= 2;
       dict->entry = realloc(dict->entry, dict->cap * sizeof(dict_entry_s));
   }
   dict->entry[dict->len].key = strdup(key);
   dict->entry[dict->len].value = value;
   dict->len++;
}

void dict_free(dict_t dict) {
    for (int i = 0; i < dict->len; i++) {
        free(dict->entry[i].key);
    }
    free(dict->entry);
    free(dict);
}

int get_hash_count(char* spring) {
    int hash_count = 0;
    for (int i = 0; i < strlen(spring); i++) {
        if (spring[i] == '#') {
            hash_count++;
            //if (spring[i + 1] != '#') {
                //return hash_count;
            //}
        }
    }
    return hash_count;
}

void get_hash(char* buffer, int hash_len, int padding_len) {
    for (int i = 0; i < padding_len; i++) {
        if (i == padding_len - 1) { buffer[i] = '\0'; }
        else if (i < hash_len) { buffer[i] = '#'; }
        else { buffer[i] = ' '; }
    }
}

int shift_left(char* str) {
    int len = strlen(str);
    if (str[len - 2] != ' ') {
        return 0;
    }
    for (int i = len - 1; i >= 0; i--) {
        if (i == 0) {
            str[i] = ' ';
            break;
        }
        str[i] = str[i - 1];
    }
    return 1;
}

int shift_right(char* str) {
    int len = strlen(str);
    if (str[0] != ' ') {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (i == len - 1) {
            str[i] = ' ';
            break;
        }
        str[i] = str[i + 1];
    }
    return 1;
}

int check_valid(char* chunk, char* spring) {
    int valid = 1;
    for (int j = 0; j < strlen(chunk); j++) {
        if (chunk[j] == '#') {
            if (spring[j] == '.') {
                valid = 0;
            }
        }
    }
    return valid;
}

int append_spring(char* padded_spring, char* spring_record) {
    for (int i = 0; i < strlen(padded_spring); i++) {
        if (spring_record[i] != ' ') {
            padded_spring[i] = spring_record[i];
        }
    }
    return 0;
}
