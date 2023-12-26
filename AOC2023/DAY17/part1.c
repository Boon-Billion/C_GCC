#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<list.h>


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



int main(){

    queue_t test = queue_new();
    enqueue(test, 10);
    enqueue(test, 20);
    enqueue(test, 30);
    enqueue(test, 40);
    enqueue(test, 50);
    list_t proto = test->head;
    for (int i = 0; i < test->size; i++){
        int value = proto->data;
        proto = proto->next;
        printf("\t%d\n", value);
    }

    int value = dequeue(test);
    value = dequeue(test);
    value = dequeue(test);
    value = dequeue(test);
    value = dequeue(test);
    value = dequeue(test);

    proto = test->head;
    for (int i = 0; i < test->size; i++){
        int value = proto->data;
        proto = proto->next;
        printf("\t%d\n", value);
    }

    list_t test1 = list_new();
    test1 = list_push(test1 , 10);
    test1 = list_push(test1 , 20);
    test1 = list_push(test1 , 30);
    test1 = list_pop(test1);

    

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