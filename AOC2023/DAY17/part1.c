#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<list.h>
#include<dict.h>

FILE* file;
int** heatmap = 0;
int** distances = 0;

char str_buffer[256] = {0};

typedef struct{
    int x;
    int y;
}point_s, *point_t;

typedef struct{
    int** graph;
    int x_len;
    int y_len;
}graph_t;

int manhattan_distance(point_t a, point_t b){
    return abs(a->x - b->x) + abs(a->y - b->y);
}

typedef struct{
    point_t point;
    int direction;
    int steps_remain;
    int cost;
}m_node_s, *m_mode_t;

int dijkstra(graph_t graph, m_mode_t source);

int main(){

    int x_len = 0;
    int y_len = 0;
    file = fopen("input.txt", "r");
    heatmap = malloc(sizeof(int*));

    while(fgets(str_buffer, 256, file)){
        heatmap = realloc(heatmap, (y_len + 1) * sizeof(int*));

        x_len = strlen(str_buffer);
        if(str_buffer[x_len - 1] == '\n'){x_len--;}

        heatmap[y_len] = malloc(x_len * sizeof(int));

        for(int i = 0; i < x_len; i++){
            heatmap[y_len][i] = str_buffer[i] - 0x30;
        }

        y_len++;
    }
    graph_t graph = {heatmap, x_len, y_len};
    m_mode_t node = malloc(sizeof(m_node_s));
    point_t point = malloc(sizeof(point_s));
    *point = (point_s){0, 0}; 
    *node = (m_node_s){point, 'n', 3, 0};
    dijkstra(graph, node);
    //free(point);
    return 0;
}

int dijkstra(graph_t graph, m_mode_t source){
    
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

    queue_t queue = queue_new(); 
    enqueue_p(queue, source, 0);
    cost[source->point->y][source->point->x] = 0;
    // for (int i = 0; i < y_len; i++){
    //     for (int j = 0; j < x_len; j++){
    //         point_t point = malloc(sizeof(point_s));
    //         point->x = j;
    //         point->y = i;
    //         enqueue_p(queue, point, &cost[i][j]);
    //     }
    // }
    //int q = 0;
    //enqueue_p(queue, source, &q);
    dict_t seen_node = dict_new();
    int loop_count = 0;
    point_t des_point = malloc(sizeof(point_s));
    des_point->x = x_len - 1;
    des_point->y = y_len - 1;
    while(queue->size){

        if(cost[y_len - 1][x_len - 1] != 1000){
            for(int i = 0; i < y_len; i++){
                for (int j = 0; j < x_len; j++){
                    printf(" %d ", graph.graph[i][j]);
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
            break;
        }
        m_mode_t node = dequeue_p(queue);
        int x = node->point->x;
        int y = node->point->y;
        char temp[256] = {0};
        char itoa_buffer[4] = {0};
        strcat(temp, itoa(y, itoa_buffer, 10));
        strcat(temp, ",");
        strcat(temp, itoa(x, itoa_buffer, 10));
        strcat(temp, ",");
        strcat(temp, itoa(node->direction, itoa_buffer, 10));
        strcat(temp, ",");
        strcat(temp, itoa(node->steps_remain, itoa_buffer, 10));
        

        strcat(temp, ",");
        strcat(temp, itoa(node->cost, itoa_buffer, 10));
        //printf("\nPOP: %s\n", temp);

        // if(visit[point->y][point->x] == 1){
        //     continue;
        // }

        for (int dir = 0; dir < 4; ++dir) {
            int dx = x + directions[dir][0];
            int dy = y + directions[dir][1];
            if(dx == dy && dx == 0){
                 continue;
             }
            if (dx >= 0 && dx < x_len && dy >= 0 && dy < y_len) {
                point_t new_point = malloc(sizeof(point_s));
                new_point->x = dx;
                new_point->y = dy;

                int new_cost = node->cost + graph.graph[dy][dx];
                int prio = manhattan_distance(new_point, des_point) + new_cost;
                m_mode_t new_node = malloc(sizeof(m_node_s));
                new_node->direction = dir;
                new_node->point = new_point;
                new_node->cost = new_cost;
                if(node->direction == new_node->direction){
                    new_node->steps_remain = node->steps_remain - 1;
                }
                else{
                    new_node->steps_remain = 2;
                }
                temp[0] = 0;
                strcat(temp, itoa(dy, itoa_buffer, 10));
                strcat(temp, ",");
                strcat(temp, itoa(dx, itoa_buffer, 10));
                strcat(temp, ",");
                strcat(temp, itoa(dir, itoa_buffer, 10));
                strcat(temp, ",");
                strcat(temp, itoa(new_node->steps_remain, itoa_buffer, 10));
                
                if(new_node->steps_remain != -1){
                    // if new_node exist, skip; dict
                    //point,direction,cost
                    //ie "1,2,3,10"
                    if(new_node->direction == 0 && node->direction == 1){
                        // printf("ignored\n");
                        continue;
                    }
                    if(new_node->direction == 1 && node->direction == 0){
                        // printf("ignored\n");
                        continue;
                    }
                    if(new_node->direction == 2 && node->direction == 3){
                        // printf("ignored\n");
                        continue;
                    }
                    if(new_node->direction == 3 && node->direction == 2){
                        // printf("ignored\n");
                        continue;
                    }

                    if (cost[dy][dx] > new_cost) {
                        cost[dy][dx] = new_cost;   
                        loop_count++;
                        printf("%d\n", loop_count);                 
                    }
                    
                    int find = dict_find(seen_node, temp, 0);
                    if(find != 0){
                        //printf("skiped: %s\n" , temp);
                    } 
                    else{
                        dict_add(seen_node, temp, 1);
                        enqueue_p(queue, new_node, prio);
                        strcat(temp, ",");
                        strcat(temp, itoa(new_cost, itoa_buffer, 10));
                        //printf("\nQueued: %s\n", temp);
                    }
                    
                    int debug = 0; 
                }

                
                
            }
        }

        //visit[y][x] = 1;
        free(node->point);
        free(node);
        //printf("%d\n", queue->size);
        if(!queue->size){
            for(int i = 0; i < y_len; i++){
                for (int j = 0; j < x_len; j++){
                    printf(" %d ", graph.graph[i][j]);
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