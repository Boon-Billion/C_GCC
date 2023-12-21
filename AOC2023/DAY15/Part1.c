#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dict.h"

int hash_aoc(char* str);
FILE* file;
char char_buffer = 0;
char str_buffer[256] = {0};
dict_t box[256] ={ 0 };

int main(){

    for(int i = 0; i < 256; i++){
        box[i] = dict_new(); 
    }

    file = fopen("input.txt", "r");

    int char_len = 0;
    int sum_hash = 0;
    while((char_buffer = fgetc(file))){
        if(char_buffer == ',' ||char_buffer == EOF){
            str_buffer[char_len] = 0;
            
            printf("\t%s", str_buffer);
            if(str_buffer[char_len - 2] == '='){
                str_buffer[char_len - 2] = 0;
                int hash = hash_aoc(str_buffer);
                dict_add(box[hash], str_buffer, str_buffer[char_len - 1] - 0x30);
            }
            else{
                str_buffer[char_len - 1] = 0;
                int hash = hash_aoc(str_buffer);
                dict_remove(box[hash], str_buffer);

            }
            char_len = 0;
            if(char_buffer == EOF){
                break;
            }
            continue;
        }
        str_buffer[char_len++] = char_buffer;
    }
    int part2_sum = 0;
    int part2 = 0;
    for(int i = 0; i < 256; i++){
        for(int j = 0; j < box[i]->len; j++){
            part2_sum += (i + 1) * (j + 1) * box[i]->entry[j].value;
            int def = 0;
        }
    }
    
    printf("\n\tPart2: %d\n", part2_sum);
    for(int i = 0; i < 256; i++){
        dict_free(box[i]);
    }
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

