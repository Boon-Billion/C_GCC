#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<list.h>


FILE* file;
int** heatmap = 0;
int** distances = 0;

char str_buffer[256] = {0};

typedef struct{
    char direction;
    int quota;
}info_t;

typedef struct{
    int x;
    int y;
}point_s, *point_t;

typedef struct{
    int** graph;
    int x_len;
    int y_len;
}graph_t;

info_t** info = 0;
int manhattan_distance(point_t a, point_t b){
    return abs(a->x - b->x) + abs(a->y - b->y);
}

int dijkstra(graph_t graph, point_t source);

int main(){

    int x_len = 0;
    int y_len = 0;
    file = fopen("input.txt", "r");
    heatmap = malloc(sizeof(int*));
    //info = malloc(sizeof(info_t*));

    while(fgets(str_buffer, 256, file)){
        heatmap = realloc(heatmap, (y_len + 1) * sizeof(int*));
        //info = realloc(info, (y_len + 1) * sizeof(info_t*));

        x_len = strlen(str_buffer);
        if(str_buffer[x_len - 1] == '\n'){x_len--;}

        heatmap[y_len] = malloc(x_len * sizeof(int));
        //info[y_len] = malloc(x_len * sizeof(info_t));

        for(int i = 0; i < x_len; i++){
            heatmap[y_len][i] = str_buffer[i] - 0x30;
            //info[y_len][i].direction = 'N';
            //info[y_len][i].quota = 0;
        }

        y_len++;
    }
    graph_t graph = {heatmap, x_len, y_len};
    point_t point = malloc(sizeof(point_s));
    *point = (point_s){0, 0};
    dijkstra(graph, point);
    //free(point);
    return 0;
}

int dijkstra(graph_t graph, point_t source){
    
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    int directions[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Up, Down, Left, Right
    int x_len = graph.x_len;
    int y_len = graph.y_len;
    int** cost = malloc(y_len * sizeof(int*));
    int** visit = malloc(y_len * sizeof(int*));

    for(int i = 0; i < y_len; i++){
        cost[i] = malloc(x_len * sizeof(int));
        visit[i] = malloc(x_len * sizeof(int));
        for(int j = 0; j < x_len; j++){    
            cost[i][j] = 1000;
            visit[i][j] = 0;
        }       
    }

    queue_t priority_q = queue_new();
    
    cost[source->y][source->x] = 0;
    for (int i = 0; i < y_len; i++){
        for (int j = 0; j < x_len; j++){
            point_t point = malloc(sizeof(point_s));
            point->x = j;
            point->y = i;
            enqueue_p(priority_q, point, &cost[i][j]);
        }
    }
    int q = 0;
    enqueue_p(priority_q, source, &q);
    while(priority_q->size){
        point_t point = dequeue_p(priority_q);
        if(visit[point->y][point->x] == 1){
            continue;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int x = point->x + directions[dir][0];
            int y = point->y + directions[dir][1];

            if (x >= 0 && x < x_len && y >= 0 && y < y_len) {
                int new_cost = graph.graph[y][x] + cost[point->y][point->x];
                if (cost[y][x] > new_cost) {
                    cost[y][x] = new_cost;                    
                }
            }
        }

        visit[point->y][point->x] = 1;
        free(point);
        //print
        if(priority_q->size == 0){
            for(int i = 0; i < y_len; i++){
                for (int j = 0; j < x_len; j++){
                    printf(" %d ", graph.graph[i][j]);
                }
                printf("\t\t");
                for (int j = 0; j < x_len; j++){
                    printf(" %d ", visit[i][j]);
                }
                
                printf("\t\t");
                for (int j = 0; j < x_len; j++){
                    if(cost[i][j]>=10){
                        printf("%d ", cost[i][j]);
                    }
                    else if(cost[i][j]>=0){
                        printf("%d  ", cost[i][j]);
                    }
                    
                    else{
                        printf("%d ", cost[i][j]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            //print end
        }
        
    }
    for(int i = 0; i < y_len; i++){
        free(cost[i]);
        free(visit[i]);     
    }
    free(cost);
    free(visit);



}