#include <stdio.h>
#include <glib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define BGRY  "\e[30;48;5;240m"
#define BRED "\e[101m"
#define BBLU "\e[104m"
#define BGRN "\e[102m"

typedef enum field {
    EMPTY = 0,
    BLOCK = 1, 
    RED_RECEPTER = 8,
    GREEN_RECEPTER = 9,
    BLUE_RECEPTER = 10
} Field;

typedef enum step {
    Up, Down, Left, Right
} Step;

typedef enum ball {
    NONE = 0,
    RED = 8, 
    GREEN = 9,
    BLUE = 10
} Ball;

typedef struct piece {
    Field field;
    Ball ball;
} Piece;

typedef struct map {
    Piece pieces[25];
    int width;
    int height;
} Map;

typedef struct playback {
    Map initialState;
    Map currentState;
    Step steps[20];
    int stepCount;
} Playback;

void printPiece(Piece p, int x, int y) {
    switch (p.field) {
        case EMPTY:
            break;
        case BLOCK:
            printf(BGRY); break;
        case RED_RECEPTER:
            printf(BRED); break;
        case GREEN_RECEPTER:
            printf(BGRN); break;
        case BLUE_RECEPTER:
            printf(BBLU); break;
        default: break;
    }

    switch (p.ball) {
        case RED:
            printf(KRED); break;
        case GREEN:
            printf(KGRN); break;
        case BLUE:
            printf(KBLU); break;
        default: break;
    }

    float fx = x/2.2f - 3.0f;
    float fy = y - 3.0f;

    if(p.ball != NONE) {
        if(fx * fx + fy * fy < 11) {
            printf("●");
        } else {
            printf(" ");
        }
    } else {
        printf(" ");
    }

    printf(KNRM);
}

void printMap(Map map) {
    for(int r = 0; r < map.height; r++) {
        for(int subRow = 0; subRow < 7; subRow++) {
            putchar('|');
            for(int c = 0; c < map.width; c++) {
                for(int subColumn = 0; subColumn < 14; subColumn++) {
                    printPiece(map.pieces[r * map.width + c], subColumn, subRow);
                }
            }
            putchar('|');
            putchar('\n');
        }
    }
}

int isSolved(Map map) {
    for(int r = 0; r < map.height; r++) {
        for(int c = 0; c < map.width; c++) {
            Piece p = map.pieces[r * map.width + c];
            if (p.ball != NONE && p.ball != p.field) {
                return 0;
            }
        }
    }
    return 1;
}

void tryMoveBall(Map *map, int x1, int y1, int x2, int y2) {
    Piece *p_src = &(map -> pieces[y1 * map -> width + x1]);
    Piece *p_dest = &(map -> pieces[y2 * map -> width + x2]);

    if (p_src -> ball != NONE && (p_dest -> ball == NONE && p_dest -> field != BLOCK)) {
        p_dest -> ball = p_src -> ball;
        p_src -> ball = NONE;
    }
}

Map up(Map map){
    for(int r = 1; r < map.height; r++) {
        for(int c = 0; c < map.width; c++) {
            tryMoveBall(&map, c, r, c, r - 1);
        }
    }
    return map;
}

Map down(Map map){
    for(int r = map.height - 2; r >= 0; r--) {
        for(int c = 0; c < map.width; c++) {
            tryMoveBall(&map, c, r, c, r + 1);
        }
    }
    return map;
}

Map right(Map map){
    for(int r = 0; r < map.height; r++) {
        for(int c = map.width - 2; c >= 0; c--) {
            tryMoveBall(&map, c, r, c + 1, r);
        }
    }
    return map;
}

Map left(Map map){
    for(int r = 0; r < map.height; r++) {
        for(int c = 1; c < map.width; c++) {
            tryMoveBall(&map, c, r, c - 1, r);
        }
    }
    return map;
}

Playback *newPlaybackNextStep(Playback p, Step nextStep, Map newState){
    Playback *newPlayback = malloc(sizeof(Playback));
    memcpy(newPlayback, &p, sizeof(Playback));

    newPlayback -> steps[(newPlayback -> stepCount)++] = nextStep;
    newPlayback -> currentState = newState;

    return newPlayback;
}

Playback *newPlayback(Map initialState) {
    Playback *newPlayback = malloc(sizeof(Playback));

    newPlayback -> initialState = initialState;
    newPlayback -> currentState = initialState;
    newPlayback -> stepCount = 0;

    return newPlayback;
}

void printSolution(Step *steps, int size){
    for(int i = 0; i < size; i++) {
        switch (steps[i]) {
            case Up: printf("Up\n"); break;
            case Down: printf("Down\n"); break;
            case Left: printf("Left\n"); break;
            case Right: printf("Right\n"); break;
            default: break;
        }
    }
}

void solve(Map map) {
    GQueue* q = g_queue_new();
    g_queue_push_tail(q, newPlayback(map));

    while(!isSolved(((Playback*)g_queue_peek_head(q)) -> currentState)
            && g_queue_get_length(q) < 1000000) {

        Playback *p = g_queue_pop_head(q);
        g_queue_push_tail(q, newPlaybackNextStep(*p, Up, up(p -> currentState)));
        g_queue_push_tail(q, newPlaybackNextStep(*p, Down, down(p -> currentState)));
        g_queue_push_tail(q, newPlaybackNextStep(*p, Left, left(p -> currentState)));
        g_queue_push_tail(q, newPlaybackNextStep(*p, Right, right(p -> currentState)));
    }

    if(g_queue_get_length(q) >= 1000000) {
        printf("Not solved\n");
    } else {
        Playback *p = g_queue_peek_head(q);
        printf("Solved:\n");
        printSolution(p -> steps, p -> stepCount);
    }

}

int main(void) {
    // Map map3x3 = {{{BLOCK, NONE},       {EMPTY, NONE}, {GREEN_RECEPTER, GREEN},
    //                {RED_RECEPTER, RED}, {EMPTY, NONE}, {EMPTY, NONE},
    //                {EMPTY, NONE},       {EMPTY, NONE}, {BLUE_RECEPTER, BLUE}}, 3, 3};
    // printMap(map3x3);
    // printf("Is solved %d\n", isSolved(map3x3));

    Map map3x3ToSolve = {{{EMPTY, NONE}, {GREEN_RECEPTER, NONE}, {BLOCK, NONE},
                          {EMPTY, NONE}, {RED_RECEPTER, GREEN},  {BLUE_RECEPTER, RED},
                          {EMPTY, NONE}, {BLOCK, NONE},          {EMPTY, BLUE}}, 3, 3};
    printMap(map3x3ToSolve);
    // printf("Is solved %d\n", isSolved(up(left(left(up(up(map3x3ToSolve)))))));
    solve(map3x3ToSolve);
    // printMap(up(map3x3ToSolve));
    // printMap(down(map3x3ToSolve));
    // printMap(left(map3x3ToSolve));
    // printMap(down(down(left(up(map3x3ToSolve)))));

    // Map map4x4 = {{{BLOCK, NONE},        {EMPTY, NONE}, {GREEN_RECEPTER, BLUE}, {GREEN_RECEPTER, BLUE},
    //                {RED_RECEPTER, NONE}, {EMPTY, RED},  {EMPTY, NONE},          {EMPTY, NONE},
    //                {RED_RECEPTER, NONE}, {EMPTY, RED},  {EMPTY, NONE},          {EMPTY, NONE},
    //                {EMPTY, NONE},        {EMPTY, NONE}, {BLUE_RECEPTER, BLUE},  {BLUE_RECEPTER, BLUE}}, 4, 4};

    // printMap(map4x4);
    // printf("Is solved %d\n", isSolved(map4x4));


}


