#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct{
    int x;
    int y;
    char direction;
}seen_entry_s;
typedef struct{
    int size;
    int cap;
    seen_entry_s* entry;
}seen_path_s, *seen_path_t; 
seen_path_t seen_new(void){
    seen_path_s proto = {0, 4, malloc(4 * sizeof(seen_entry_s))};
    seen_path_t d = malloc(sizeof(seen_path_s));
    *d = proto;
    return d;
}
void seen_add(seen_path_t seen_path, int x, int y, char direction){
    if(seen_path->cap == seen_path->size){
        seen_path->cap*=2;
        seen_path->entry = realloc(seen_path->entry, seen_path->cap * sizeof(seen_entry_s));
    }
    seen_path->entry[seen_path->size].direction = direction;
    seen_path->entry[seen_path->size].x = x;
    seen_path->entry[seen_path->size].y = y;
    seen_path->size++;
}
int seen_search(seen_path_t seen_path, int x, int y, char direction){
    for(int i = 0; i < seen_path->size; i++){
        char cmp_direction = seen_path->entry[i].direction;
        int cmp_x = seen_path->entry[i].x;
        int cmp_y = seen_path->entry[i].y;
        if (cmp_direction == direction && cmp_x == x && cmp_y == y){
            return 1;
        }
    }
    return 0;
}
void seen_free(seen_path_t seen_path){
    free(seen_path->entry);
    free(seen_path);
}
char new_direction(char direction, char mirror_type);
int dfs(char** input, char** tag, int point[2], char direction, seen_path_t seen_path);
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
    char** tag = calloc(line_len + 1, sizeof(char*));
    for(int i = 0; i < line_len; i++){
        tag[i] = calloc(strlen(input[0]) + 1, sizeof(char*));
        memset(tag[i], ' ', strlen(input[0]));
    }
    tag[line_len] = 0; 
    for(int i = 0; i < line_len; i++){
        printf("\t%s\n", input[i]);
    }
    int point[2] = {0, 0}; 
    seen_path_t  seen_path = seen_new();
    int check = dfs(input, tag, point, 'R', seen_path);
    seen_free(seen_path);
    printf("\n\tPart1: %d\n", check);
    ////part2////
    int max_check = 0;
    for(int i = 0; i < line_len; i++){
        for(int i = 0; i < line_len; i++){
            memset(tag[i], ' ', strlen(input[0]));
        }
        tag[line_len] = 0;
        int point[2] = {0, i}; 
        seen_path_t seen_path = seen_new();
        int check = dfs(input, tag, point, 'R', seen_path);
        if(check > max_check){
            max_check = check;
        }
        seen_free(seen_path);
    }
    for(int i = 0; i < line_len; i++){
        for(int i = 0; i < line_len; i++){
            memset(tag[i], ' ', strlen(input[0]));
        }
        tag[line_len] = 0;
        int point[2] = {(strlen(input[0]) - 1), i}; 
        seen_path_t seen_path = seen_new();
        int check = dfs(input, tag, point, 'L', seen_path);
        if(check > max_check){
            max_check = check;
        }
        seen_free(seen_path);
    }
    for(int i = 0; i < strlen(input[0]); i++){
        for(int i = 0; i < line_len; i++){
            memset(tag[i], ' ', strlen(input[0]));
        }
        tag[line_len] = 0;
        int point[2] = {i, 0}; 
        seen_path_t seen_path = seen_new();
        int check = dfs(input, tag, point, 'D', seen_path);
        if(check > max_check){
            max_check = check;
        }
        seen_free(seen_path);
    }
    for(int i = 0; i < strlen(input[0]); i++){
        for(int i = 0; i < line_len; i++){
            memset(tag[i], ' ', strlen(input[0]));
        }
        tag[line_len] = 0;
        int point[2] = {i, line_len - 1}; 
        seen_path_t seen_path = seen_new();
        int check = dfs(input, tag, point, 'U', seen_path);
        if(check > max_check){
            max_check = check;
        }
        seen_free(seen_path);
    }
    
    printf("\n\tPart2: %d", max_check);
    return 0;
}
char new_direction(char direction, char mirror_type){
    switch (mirror_type){
        case '|':
            if(direction == 'R' || direction == 'L'){
                return '|';
            }
            return direction;
        case '-':
            if(direction == 'U' || direction == 'D'){
                return '-';
            }
            return direction;
        case '/':
            if(direction == 'U'){return 'R';}
            else if(direction == 'D'){return 'L';}
            else if(direction == 'R'){return 'U';}
            else if(direction == 'L'){return 'D';}
        break;
        case '\\':
            if(direction == 'U'){return 'L';}
            else if(direction == 'D'){return 'R';}
            else if(direction == 'R'){return 'D';}
            else if(direction == 'L'){return 'U';}
        break;
    }
}


int dfs(char** input, char** tag, int _point[2], char _direction, seen_path_t seen_path){
    char direction = _direction;
    int point[2] = {_point[0], _point[1]};
    int str_len = strlen(input[0]);
    int line_len  = 0;
    while(input[++line_len]);
    int x = point[0];
    int y = point[1];
    
    if(seen_search(seen_path, point[0], point[1], direction)){
        return 0;
    }
    seen_add(seen_path, point[0], point[1], direction);
    int count = 0; 
    char new_dir = 0;
    switch (direction){
    case 'R':
        for(int i = point[0]; i < str_len; i++){
            if(tag[point[1]][i] != ' ' && i == point[0]){
                continue;
            }
            if(tag[point[1]][i] == ' '){
                count++;
            }
            if(input[point[1]][i] != '.'){
                new_dir = new_direction(direction, input[point[1]][i]);
                tag[point[1]][i] = input[point[1]][i]; //TODO TAG FN
                point[0] = i;
                break;
            }
            else{
                tag[point[1]][i] = '#';
                point[0] = i;
                if(i == str_len - 1){     
                    return count;
                }
            }
        }        
        break;
    
    case 'L':
        for(int i = point[0]; i >=0; i--){
            if(tag[point[1]][i] != ' ' && i == point[0]){
                continue;
            }
            if(tag[point[1]][i] == ' '){
                count++;
            }
            if(input[point[1]][i] != '.'){
                new_dir = new_direction(direction, input[point[1]][i]);
                tag[point[1]][i] = input[point[1]][i]; //TODO TAG FN
                point[0] = i;
                break;
            }
            else{
                tag[point[1]][i] = '#';
                point[0] = i;
                if(i == 0){
                    return count;
                }
            }
        }
        break;
    case 'D':
        for(int i = point[1]; i < line_len; i++){
            if(tag[i][point[0]] != ' ' && i == point[1]){
                continue;
            }
            if(tag[i][point[0]] == ' '){
                count++;
            }
            if(input[i][point[0]] != '.'){
                new_dir = new_direction(direction, input[i][point[0]]);
                tag[i][point[0]] = input[i][point[0]]; //TODO TAG FN
                point[1] = i;
                break;
            }
            else{
                tag[i][point[0]] = '#';
                point[1] = i;
                if(i == line_len - 1){
                    return count;
                }
            }
        }
        break;
    case 'U':
        for(int i = point[1]; i >= 0; i--){
            if(tag[i][point[0]] != ' ' && i == point[1]){
                continue;
            }
            if(tag[i][point[0]] == ' '){
                count++;
            }
            if(input[i][point[0]] != '.'){
                new_dir = new_direction(direction, input[i][point[0]]);
                tag[i][point[0]] = input[i][point[0]]; //TODO TAG FN
                point[1] = i;
                break;
            }
            else{
                tag[i][point[0]] = '#';
                point[1] = i;
                if(i == 0){
                    return count;
                }
            }
        } 
        break;
    default:
        break;
    }
    if(new_dir == '-'){
        count += dfs(input, tag, point, 'R' ,seen_path);
        count += dfs(input, tag, point, 'L' ,seen_path);
    }
    else if(new_dir == '|'){
        count += dfs(input, tag, point, 'D' ,seen_path);
        count += dfs(input, tag, point, 'U' ,seen_path);
    }
    else{
        count += dfs(input, tag, point, new_dir ,seen_path);
    }
    return count;
}