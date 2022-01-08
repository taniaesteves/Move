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

typedef enum piece {
    EMPTY = 0,
    BLOCK = 1,
    RED_RECEPTER = 2,
    GREEN_RECEPTER = 3,
    BLUE_RECEPTER = 4,

    RED_BALL = 64,
    GREEN_BALL = 128,
    BLUE_BALL = 192,

} Piece;

void printChar(Piece p, int x, int y) {
    switch (p & 63) {
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

    switch (p & 448) {
        case RED_BALL:
            printf(KRED); break;
        case GREEN_BALL:
            printf(KGRN); break;
        case BLUE_BALL:
            printf(KBLU); break;
        default: break;
    }

    x -= 2;
    y -= 5;
    if(p & 448) {
        if(x * x + y * y < 8) {
            printf("●");
        } else {
            printf(" ");
        }
    } else {
        printf(" ");
    }

    printf(KNRM);
}

void print(Piece map[3][3], int height, int width) {
    for(int r = 0; r < height; r++) {
        for(int subRow = 0; subRow < 5; subRow++) {
            for(int c = 0; c < width; c++) {
                for(int subColumn = 0; subColumn < 10; subColumn++) {
                    printChar(map[r][c], subRow, subColumn);
                }
            }
            putchar('\n');
        }
    }
}



int main(void) {
    Piece map[3][3] = {
        {BLOCK,          EMPTY,                 GREEN_RECEPTER | BLUE_BALL},
        {RED_RECEPTER,   EMPTY | RED_BALL,      EMPTY},
        {EMPTY,          EMPTY,                 BLUE_RECEPTER}
    };

    print(map, 3, 3);

}


