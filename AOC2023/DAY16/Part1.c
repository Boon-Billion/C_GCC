#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* new_direction(char direction, char mirror_type);

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
    int** tag = calloc(line_len + 1, sizeof(int*));
    for(int i = 0; i < line_len; i++){
        tag[i] = calloc(strlen(input[0]), sizeof(int*));
    }
    tag[line_len] = 0; 
    for(int i = 0; i < line_len; i++){
        printf("\t%s\n", input[i]);
    }
    int point[2] = {0, 0};
    char* test = new_direction('U', '|');
    return 0;
}

char* new_direction(char direction, char mirror_type){
    switch (mirror_type){
        case '|':
            if(direction == 'R' || direction == 'L'){
                return strdup("DU");
            }
            return strdup((char[2]){direction, '\0'});

        case '-':
            if(direction == 'U' || direction == 'D'){
                return strdup("RL");
            }
            return strdup((char[2]){direction, '\0'});

        case '/':
            if(direction == 'U'){
                return strdup("R");
            }
            else if(direction == 'D'){
                return strdup("L");
            }
            else if(direction == 'R'){
                return strdup("U");
            }
            else if(direction == 'L'){
                return strdup("D");
            }
        break;

        case '\\':
            if(direction == 'U'){
                return strdup("L");
            }
            else if(direction == 'D'){
                return strdup("R");
            }
            else if(direction == 'R'){
                return strdup("D");
            }
            else if(direction == 'L'){
                return strdup("U");
            }
        break;

    }
}

int dfs(char** input, int** tag, int point[2], char direction){
    int str_len = strlen(input[0]);
    int line_len  = 0;
    while(input[++line_len]);

    switch (direction){
    case 'L':
        for(int i = point[0]; i < str_len; i++){
            if(input[point[1]][i] == '|'){

            }
        }
        break;
    
    default:
        break;
    }
}