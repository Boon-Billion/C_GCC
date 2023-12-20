#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int get_vertical(char** input);
int get_horizental(char** input);


FILE* file = NULL;
char str_buffer[256];
int main(void){
    if(fopen_s(&file, "input.txt", "r")){
        printf("file open error\n");
    }
    int line_len = 0;
    char** input = (char**)malloc(sizeof(char*));
    long long part1 = 0;
    while(fgets(str_buffer, 256, file)){
        if(str_buffer[0] != '\n'){
            line_len++;
            input = realloc(input, line_len * sizeof(char*));
            input[line_len - 1] = strdup(str_buffer);
            printf("\t%s", str_buffer);
        }
        else{
            input = realloc(input, (line_len + 1) * sizeof(char*));
            input[line_len] = 0;
            int test = 0;
            if((test = get_vertical(input)) > 0){
                part1 +=  test;
            }
            else if((test = get_horizental(input)) > 0){
                part1 +=  100*test;
            }

            line_len = 0;
            debug = 0;
        }        
    }
    printf("\n\tPart1: %lld\n", part1);   
    return 0;
}

int get_vertical(char** input){
    int hori_len = strlen(input[0]);
    int vert_len = 0;
    while(input[++vert_len]);
    //transpost
    char** transpose = (char**)malloc((hori_len + 1) * sizeof(char*));
    transpose[hori_len] = 0;
    for (int i = 0; i < hori_len; i++){
        transpose[i] = (char*)malloc((vert_len + 1) * sizeof(char));
        for (int j = 0; j < vert_len; j++){ 
            transpose[i][j] = input[j][i]; 
        }
        transpose[i][vert_len] = 0;
    }

    for(int i = 0; i < hori_len - 1; i++){
        int offset = 0;
        while(!strcmp(transpose[i-offset], transpose[i + 1 + offset])){         
            if(i-offset == 0 || i+offset+1 == hori_len - 2){
                return i + 1;
            }
            else if( (i-offset)>0 && (i+offset+1)<(hori_len - 2) ){
                offset++; 
                continue;
            }
        }
    }
    return -1;
}

int get_horizental(char** input){
    int hori_len = strlen(input[0]);
    int vert_len = 0;
    while(input[++vert_len]);

    for(int i = 0; i < vert_len - 1; i++){
        int offset = 0;
        int count = 0;
        while(!strcmp(input[i - offset], input[i + 1 + offset])){                   
            if(i-offset == 0 || i+offset+1 == vert_len - 1){
                return i + 1;
            }
            else if( (i-offset)>0 && (i+offset+1)<(vert_len - 1) ){
                offset++;
                continue;
            }
             
        }
    }
    return -1;
}