#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE* file;
char str_buffer[256];

int main(){
    file = fopen("input.txt", "r");
    char** input = malloc(sizeof(char*));
    int line_len = 0;
    while(fgets(str_buffer, 256, file)){
        line_len++;
        input = realloc(input, (line_len + 1) * sizeof(char*));

        int len = strlen(str_buffer);
        if(str_buffer[len - 1]=='\n'){
            str_buffer[len - 1] = 0;
            len--;
        }
        input[line_len - 1] = strdup(str_buffer);
    }
    input[line_len] = 0;

    for(int i = 0; i < line_len; i++){
        printf("\t%s\n", input[i]);
    }
    return 0;
}