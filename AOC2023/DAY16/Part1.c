#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char new_direction(char direction, char mirror_type);
int dfs(char** input, char** tag, int point[2], char direction);
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
    int point[2] = {1, 0}; 
    int check = dfs(input, tag, point, 'R');
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

int dfs(char** input, char** tag, int _point[2], char _direction){
    char direction = _direction;
    int point[2] = {_point[0], _point[1]};
    int str_len = strlen(input[0]);
    int line_len  = 0;
    while(input[++line_len]);

    //if over limit
    //if mirror prevous reflected

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
                printf("\n");
                for(int i = 0; i < line_len; i++){
                    printf("\t%s\n", tag[i]);
                }               
                break;
            }
            else{
                tag[point[1]][i] = '#';
                point[0] = i;
            }
            printf("\n");
            for(int i = 0; i < line_len; i++){
                printf("\t%s\n", tag[i]);
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
                printf("\n");
                for(int i = 0; i < line_len; i++){
                    printf("\t%s\n", tag[i]);
                }               
                break;
            }
            else{
                tag[point[1]][i] = '#';
                point[0] = i;
            }
            printf("\n");
            for(int i = 0; i < line_len; i++){
                printf("\t%s\n", tag[i]);
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
                printf("\n");
                for(int i = 0; i < line_len; i++){
                    printf("\t%s\n", tag[i]);
                }               
                break;
            }
            else{
                tag[i][point[0]] = '#';
                point[1] = i;
            }
            printf("\n");
            for(int i = 0; i < line_len; i++){
                printf("\t%s\n", tag[i]);
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
                printf("\n");
                for(int i = 0; i < line_len; i++){
                    printf("\t%s\n", tag[i]);
                }               
                break;
            }
            else{
                tag[i][point[0]] = '#';
                point[1] = i;
            }
            printf("\n");
            for(int i = 0; i < line_len; i++){
                printf("\t%s\n", tag[i]);
            } 
        }
        break;

    default:
        break;
    }
    if(new_dir == '-'){
        count += dfs(input, tag, point, 'R');
        count += dfs(input, tag, point, 'L');
    }
    else if(new_dir == '|'){
        count += dfs(input, tag, point, 'D');
        count += dfs(input, tag, point, 'U');
    }
    else{
        count += dfs(input, tag, point, new_dir);
    }

    return count;
}