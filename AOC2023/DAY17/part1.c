#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


FILE* file;
int** headmap = 0;
int** distances = 0;

char str_buffer[256] = {0};

typedef struct{
    char direction;
    int quota;
}info_t;

typedef struct{
    int x;
    int y;
}point_t;

info_t** info = 0;
int manhattan_distance(point_t a, point_t b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}
int dijkstra(int** graph, point_t source){

}

typedef struct node{
    int data;
    struct node* next;
}list_s, *list_t;


list_t list_push(list_t list, int data){
    if(list == 0){
        list = malloc(sizeof(list_s));
        list->data = data;
        list->next = 0;
        return list;
    }
    else{
        list_t new_list = malloc(sizeof(list_s));
        new_list->data = data;
        new_list->next = list;
        return new_list;
    }
}

int main(){

    list_t test = 0;
    test = list_push(test, 10);
    test = list_push(test, 20);
    list_t test1 = 0;
    test1 = list_push(test1, 100);
    test1 = list_push(test1, 200);
    int x_len = 0;
    int y_len = 0;
    file = fopen("input.txt", "r");
    headmap = malloc(sizeof(int*));
    distances = malloc(sizeof(int*));
    info = malloc(sizeof(info_t*));

    while(fgets(str_buffer, 256, file)){
        headmap = realloc(headmap, (y_len + 1) * sizeof(int*));
        distances = realloc(distances, (y_len + 1) * sizeof(int*));
        info = realloc(info, (y_len + 1) * sizeof(info_t*));

        x_len = strlen(str_buffer);
        if(str_buffer[x_len - 1] == '\n'){x_len--;}

        headmap[y_len] = malloc(x_len * sizeof(int));
        distances[y_len] = malloc(x_len * sizeof(int));
        info[y_len] = malloc(x_len * sizeof(info_t));

        for(int i = 0; i < x_len; i++){
            headmap[y_len][i] = str_buffer[i] - 0x30;
            distances[y_len][i] = -1;
            info[y_len][i].direction = 'N';
            info[y_len][i].quota = 0;
        }

        y_len++;
    }

    for (int i = 0; i < y_len; i++){
        for (int j = 0; j < x_len; j++){
            printf(" %d ", headmap[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < x_len; j++){
            printf("%d ", distances[i][j]);
        }
        printf("\n");
    }
    return 0;
}