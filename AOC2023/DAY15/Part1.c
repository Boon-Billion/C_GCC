#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dict.h>


int hash_aoc(char* str);
FILE* file;
char char_buffer = 0;
char str_buffer[256] = {0};
int main(){

    dict_t test = dict_new();
    // dict_add(test, "index0", 120);
    // dict_add(test, "index1", 121);
    // dict_add(test, "index2", 122);
    // dict_add(test, "index3", 123);

    // dict_remove(test, "index2");

    file = fopen("input.txt", "r");

    int char_len = 0;
    int sum_hash = 0;
    while((char_buffer = fgetc(file))){
        if(char_buffer == ',' ||char_buffer == EOF){
            str_buffer[char_len] = 0;
            char_len = 0;
            printf("\t%s", str_buffer);
            sum_hash += hash_aoc(str_buffer);
            if(char_buffer == EOF){
                break;
            }
            continue;
        }
        
        str_buffer[char_len++] = char_buffer;
    }
    printf("\n\tPart1: %d\n", sum_hash);
    return 0;
}

int hash_aoc(char* str){
    int hash = 0;
    int str_len = strlen(str);
    for(int i = 0; i < str_len; i++){
        hash += str[i];
        hash *= 17;
        hash %= 256;
        int test = 0;
    }
    return hash;
}

