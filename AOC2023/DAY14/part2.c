#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int spin_cycle(char** input);



FILE* file = NULL;
char str_buffer[256] = { 0 };
int main(){
    char** input = malloc(sizeof(char*));
    int line_len = 0;

    file = fopen("input.txt","r");
    while(fgets(str_buffer, 256, file)){
        line_len++;
        input = realloc(input, line_len * sizeof(char*));
        input[line_len - 1] = strdup(str_buffer);
        printf("\t%s", str_buffer);
    }
    input = realloc(input, (line_len + 1) * sizeof(char*));
    input[line_len] = NULL;

    spin_cycle(input);

    

    return 0;
}

int spin_cycle(char** input){
    size_t str_len = strlen(input[0]) - 1;
    size_t line_len = 0;
    while(input[++line_len]);
    
    int** new_input = malloc(line_len + 1 * sizeof(char*));
    new_input[line_len] = NULL;
    int* weight = malloc(str_len * sizeof(int));
    int* tag = malloc(str_len * sizeof(int));
    memset(weight, 0, str_len * sizeof(int));
    for(int i = 0; i < str_len; i++){
        tag[i] = line_len;
    }
    /*
        N:  i = 0; i < line_len
            j = 0; j < str_len
        
        S:  i = line_len - 1; i <= 0
            j = 0; j < str_len
        
        W:  j = 0; j < str_len
            i = 0; i < line_len

        E:  j = str_len - 1; j <= 0;
            i = 0; i < line_len
    */
    for(int i = 0; i < line_len; i++){
        for(int j = 0; j < str_len; j++){
            char c_input = input[i][j];
            if(c_input == 'O'){
                weight[j] += tag[j];
                tag[j]--;
            }
            else if (c_input == '#'){
                tag[j] = line_len - i - 1;
            }         
        }
        int test = 0;
    }
    int sum = 0;
    for(int i = 0; i < str_len; i++){
        sum += weight[i];
    }

    printf("\n\n\tPart1: %d\n\n", sum);
}