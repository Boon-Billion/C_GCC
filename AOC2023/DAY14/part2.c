#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int spin_north(char** input);
void spin_west(char** input);
void spin_south(char** input);
int spin_east(char** input);
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
        int len = strlen(input[line_len - 1]);
        if (input[line_len - 1][len - 1] == '\n'){
            input[line_len - 1][len - 1] = 0;
        }
        printf("\t%s", str_buffer);
    }
    input = realloc(input, (line_len + 1) * sizeof(char*));
    input[line_len] = NULL;
    int limit = 500;
    int malloc_f = 0;
    int max_seq_len = 100;
    int tot = 0;
    int her = 0;
    int* seq = malloc(max_seq_len * sizeof(int));
    int j = 0;
    for (int i = 0; i<limit; i++){
        spin_north(input);
        spin_west(input);
        spin_south(input);
        int sum = spin_east(input);
        if(!malloc_f && i == limit - 1 ){
            malloc_f = 1;
            limit = limit+ max_seq_len;
        }
        else if(malloc_f){
            seq[j++] = sum;
            if(j == 100){
                int offset = 1;
                for (int k = 0; k < 100; k++){
                    if(seq[k] == seq[k+offset]){
                        if(k == offset){
                            i + (offset*n);
                        }
                    }
                    else{
                        offset++;
                    }
                }
                int test = 0;
            }
            malloc_f = 0;
        }
        printf("\n\t%d", sum);
    }
    
    //printf("\n\n\tPart1: %d\n\n", sum);

    return 0;
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
int spin_north(char** input){
    size_t str_len = strlen(input[0]);
    size_t line_len = 0;
    while(input[++line_len]);
    
    char** new_input = malloc((line_len + 1) * sizeof(char*));
    new_input[line_len] = NULL;
    //int* weight = malloc(str_len * sizeof(int));
    int* tag = malloc(str_len * sizeof(int));
    //memset(weight, 0, str_len * sizeof(int));
    for(int i = 0; i < str_len; i++){
        tag[i] = line_len;
    }
    
    for(int i = 0; i < line_len; i++){
        new_input[i] = (char*)malloc((str_len + 1) * sizeof(char));
        memset(new_input[i], '.', (str_len) * sizeof(char));
        new_input[i][str_len] = 0;
        for(int j = 0; j < str_len; j++){
            char c_input = input[i][j];
            if(c_input == 'O'){
                //weight[j] += tag[j];
                new_input[line_len - tag[j]][j] = 'O';
                tag[j]--;
            }
            else if (c_input == '#'){
                tag[j] = line_len - i - 1;
                new_input[i][j] = '#';
            }         
        }
        int test = 0;
    }

    

    //printf("\n");
    for(int i = 0; i < line_len; i++){
        strcpy(input[i], new_input[i]);
        free(new_input[i]);
        //printf("\n\t%s", input[i]);
    }
    //printf("\n");
    free(new_input[line_len]);
    free(new_input);
    //free(weight);
    free(tag);

    //return sum;
}

void spin_west(char** input){
    size_t str_len = strlen(input[0]);
    size_t line_len = 0;
    while(input[++line_len]);
    
    char** new_input = malloc((line_len + 1) * sizeof(char*));
    new_input[line_len] = NULL;
    int* tag = malloc(str_len * sizeof(int));
    for(int i = 0; i < str_len; i++){
        tag[i] = line_len;
    }
    for (int i = 0; i < line_len; i++){
        new_input[i] = (char*)malloc((str_len + 1) * sizeof(char));
        memset(new_input[i], '.', (str_len) * sizeof(char));
        new_input[i][str_len] = 0;
    }
    for(int j = 0; j < str_len; j++){
        for(int i = 0; i < line_len; i++){
            char c_input = input[i][j];
            if(c_input == 'O'){
                new_input[i][line_len - tag[i]] = 'O';
                tag[i]--;
            }
            else if (c_input == '#'){
                tag[i] = line_len - j - 1;
                new_input[i][j] = '#';
            }         
        }
        int test = 0;
    }

    for(int i = 0; i < line_len; i++){
        strcpy(input[i], new_input[i]);
        free(new_input[i]);
    }
    free(new_input[line_len]);
    free(new_input);
    free(tag);
}

void spin_south(char** input){
    size_t str_len = strlen(input[0]);
    size_t line_len = 0;
    while(input[++line_len]);
    
    char** new_input = malloc((line_len + 1) * sizeof(char*));
    new_input[line_len] = NULL;
    int* tag = malloc(str_len * sizeof(int));
    for(int i = 0; i < str_len; i++){
        tag[i] = line_len;
    }
    for (int i = 0; i < line_len; i++){
        new_input[i] = (char*)malloc((str_len + 1) * sizeof(char));
        memset(new_input[i], '.', (str_len) * sizeof(char));
        new_input[i][str_len] = 0;
    }
    for(int i = line_len - 1; i >= 0; i--){
        for(int j = 0; j < str_len; j++){
            char c_input = input[i][j];
            if(c_input == 'O'){
                new_input[tag[j] - 1][j] = 'O';
                tag[j]--;
            }
            else if (c_input == '#'){
                tag[j] = i;
                new_input[i][j] = '#';
            }         
        }
        int test = 0;
    }

    for(int i = 0; i < line_len; i++){
        strcpy(input[i], new_input[i]);
        free(new_input[i]);
    }
    free(new_input[line_len]);
    free(new_input);
    free(tag);
}

int spin_east(char** input){
    size_t str_len = strlen(input[0]);
    size_t line_len = 0;
    while(input[++line_len]);
    
    char** new_input = malloc((line_len + 1) * sizeof(char*));
    new_input[line_len] = NULL;
    int* tag = malloc(str_len * sizeof(int));
    int* weight = malloc(str_len * sizeof(int));
    memset(weight, 0, str_len * sizeof(int));
    for(int i = 0; i < str_len; i++){
        tag[i] = line_len;
    }
    for (int i = 0; i < line_len; i++){
        new_input[i] = (char*)malloc((str_len + 1) * sizeof(char));
        memset(new_input[i], '.', (str_len) * sizeof(char));
        new_input[i][str_len] = 0;
    }
    for(int j = str_len - 1; j >= 0; j--){
        for(int i = 0; i < line_len; i++){
            char c_input = input[i][j];
            if(c_input == 'O'){
                weight[tag[i] - 1] += line_len - i;
                new_input[i][tag[i] - 1] = 'O';
                tag[i]--;
            }
            else if (c_input == '#'){
                tag[i] = j;
                new_input[i][j] = '#';
            }         
        }
        int test = 0;
    }

    int sum = 0;
    for(int i = 0; i < str_len; i++){
         sum += weight[i];
    }
    //printf("\n");
    for(int i = 0; i < line_len; i++){
        strcpy(input[i], new_input[i]);
        //printf("\n\t%s", input[i]);
        free(new_input[i]);
    }
    free(new_input[line_len]);
    free(new_input);
    free(weight);
    free(tag);
    return sum;
}