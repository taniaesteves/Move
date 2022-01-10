#include <stdio.h>

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
    printf("Is solved %d\n", isSolved(map3x3ToSolve));

    // Map map4x4 = {{{BLOCK, NONE},        {EMPTY, NONE}, {GREEN_RECEPTER, BLUE}, {GREEN_RECEPTER, BLUE},
    //                {RED_RECEPTER, NONE}, {EMPTY, RED},  {EMPTY, NONE},          {EMPTY, NONE},
    //                {RED_RECEPTER, NONE}, {EMPTY, RED},  {EMPTY, NONE},          {EMPTY, NONE},
    //                {EMPTY, NONE},        {EMPTY, NONE}, {BLUE_RECEPTER, BLUE},  {BLUE_RECEPTER, BLUE}}, 4, 4};

    // printMap(map4x4);
    // printf("Is solved %d\n", isSolved(map4x4));


}


