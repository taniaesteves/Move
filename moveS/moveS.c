//
//  main.c
//  MoveS
//
//  Created by Noob && Heidi on 18/12/14.
//  Copyright (c) 2014 Noob && Heidi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define NBOLAS 3

#define VERMELHO 1
#define AZUL 2
#define VERDE 3
#define BLOCO -1
#define LIVRE 0


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


typedef struct bolas {
    int posx;
    int posy;
    int cor;
} *listaBolas;


listaBolas copia (listaBolas bolas) {
    listaBolas res = (listaBolas) malloc(sizeof(struct bolas) * NBOLAS);
    int i;
    
    for (i = 0; i < NBOLAS; i++) {
        res[i].cor = bolas[i].cor;
        res[i].posx = bolas[i].posx;
        res[i].posy = bolas[i].posy;
    }
    
    return res;
}

int ocupado (int x, int y, listaBolas bolas) {
    int i, res = 0;
    for (i = 0; i < NBOLAS && !res; i++) {
        if (bolas[i].posx == x && bolas[i].posy == y ) {
            res = 1;
        }
    }
    return res;
}

listaBolas direita(int mat[3][3], listaBolas bolas){
    int i;
    listaBolas res = copia(bolas);
    
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posx == 1) {
            if (mat[res[i].posy][res[i].posx + 1] != BLOCO && !ocupado(res[i].posx + 1, res[i].posy, res)) {
                res[i].posx++;
            }
        }
    }
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posx == 0) {
            if (mat[res[i].posy][res[i].posx + 1] != BLOCO && !ocupado(res[i].posx + 1, res[i].posy, res)) {
                res[i].posx++;
            }
        }
    }
    
    return res;
}


listaBolas esquerda(int mat[3][3], listaBolas bolas){
    int i;
    listaBolas res = copia(bolas);
    
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posx == 1) {
            if (mat[res[i].posy][res[i].posx - 1] != BLOCO && !ocupado(res[i].posx - 1, res[i].posy, res)) {
                res[i].posx--;
            }
        }
    }
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posx == 2) {
            if (mat[res[i].posy][res[i].posx - 1] != BLOCO && !ocupado(res[i].posx - 1, res[i].posy, res)) {
                res[i].posx--;
            }
        }
    }
    
    return res;
}


listaBolas cima(int mat[3][3], listaBolas bolas){
    int i;
    listaBolas res = copia(bolas);
    
        
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posy == 1) {
            if (mat[res[i].posy - 1][res[i].posx] != BLOCO && !ocupado(res[i].posx, res[i].posy - 1, res)) {
                res[i].posy--;
            }
        }
    }
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posy == 2) {
            if (mat[res[i].posy - 1][res[i].posx] != BLOCO && !ocupado(res[i].posx, res[i].posy - 1, res)) {
                res[i].posy--;
            }
        }
    }

    
    return res;
}


listaBolas baixo(int mat[3][3], listaBolas bolas){
    int i;
    listaBolas res = copia(bolas);
    
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posy == 1) {
            if (mat[res[i].posy + 1][res[i].posx] != BLOCO && !ocupado(res[i].posx, res[i].posy + 1, res)) {
                res[i].posy++;
            }
        }
    }
    
    for (i = 0; i < NBOLAS; i++) {
        if (res[i].posy == 0) {
            if (mat[res[i].posy + 1][res[i].posx] != BLOCO && !ocupado(res[i].posx, res[i].posy + 1, res)) {
                res[i].posy++;
            }
        }
    }
    
    return res;
}


//imprimeLinha (i, mapa, pecas)
    // y = (int)i/5;
    // linha = i%5;
    // ciclo x = 0 até 2
        //  if bloco
        //        printf ("///////");
        //  if existeBolaEmXY
                //if Mat[X][Y] for colorida
                    ////////////Imprimir bola em XY com cor
                //else
                    ////////////Imprimir bola " ***** " -> (l = 0 ou 3)
                
            //else
                //if Mat[X][Y] for colorida
                    ////////////Imprimir XY com cor
                //else
                    ////////////Imprimir "       "
                    
        // printf ("|")
        
        
        
int corBola (int x, int y, listaBolas bolas){
    int i;
    
    for (i = 0; i < NBOLAS; i++) {
        if(bolas[i].posx == x && bolas[i].posy == y)
              return bolas[i].cor;       
    }
    
    return 0;
    
}


void imprimeLinha (int i, int mat[3][3], listaBolas bolas){
    int y = (int) i/5, linha = i%5, x;
    
    //printf("")
    
    for (x = 0; x < 3; x ++) {
        if (mat[y][x] == -1)
            printf (BGRY "       " KNRM);
        else
            if (ocupado (x, y, bolas)) {
                if (mat[y][x] > 0) {
                    if (linha == 1 || linha == 4) {
                        switch (mat[y][x]) {
                            case 1:
                                printf(BRED " ");
                              break;    
                            case 2:
                                printf(BBLU " ");
                              break;
                            case 3:
                                printf(BGRN " ");
                              break;
                        }
                        
                        switch (corBola(x, y, bolas)) {///ESTAMOS AQUI
                            case 1:
                                printf(KRED "●●●");
                              break;    
                            case 2:
                                printf(KBLU "●●●");
                              break;
                            case 3:
                                printf(KGRN "●●●");
                              break;
                        }
                        
                        switch (mat[y][x]) {
                            case 1:
                                printf(BRED " " KNRM);
                              break;    
                            case 2:
                                printf(BBLU " " KNRM);
                              break;
                            case 3:
                                printf(BGRN " " KNRM);
                              break;
                        }
                        
                    }
                    else {
                        
                        switch (mat[y][x]) {
                            case 1:
                                printf(BRED);
                              break;    
                            case 2:
                                printf(BBLU);
                              break;
                            case 3:
                                printf(BGRN);
                              break;
                        }
                        
                        
                        switch (corBola(x, y, bolas)) {
                            case 1:
                                printf(KRED "●●●" KNRM);
                              break;    
                            case 2:
                                printf(KBLU "●●●" KNRM);
                              break;
                            case 3:
                                printf(KGRN "●●●" KNRM);
                              break;
                        }
                    }
                }
                
                else {
                    if (linha == 1 || linha == 4) {

                        printf(" ");
                        
                        switch (corBola(x, y, bolas)) {
                            case 1:
                                printf(KRED "●●●" KNRM);
                              break;    
                            case 2:
                                printf(KBLU "●●●" KNRM);
                              break;
                            case 3:
                                printf(KGRN "●●●" KNRM);
                              break;
                        }
                        
                        printf(" ");
                    }
                    else {
                        switch (corBola(x, y, bolas)) {
                            case 1:
                                printf(KRED "●●●●" KNRM);
                              break;    
                            case 2:
                                printf(KBLU "●●●●" KNRM);
                              break;
                            case 3:
                                printf(KGRN "●●●●" KNRM);
                              break;
                        }
                    }
                }
            }
            
            else {
                // colocar cores
                if (mat[y][x] > 0) {
                    switch (mat[y][x]) {
                        case 1:
                            printf(BRED "       " KNRM);
                            break;    
                        case 2:
                            printf(BBLU "       " KNRM);
                            break;
                        case 3:
                            printf(BGRN "       " KNRM);
                            break;
                        }
                }
                
                else {
                    printf ("       ");
                    
                }
            }
        
       //printf("|");
    }
    
}


// Imprimir " - - - - - - - - - - - - "
// ciclo i = 1
    // Imprimir '|'
    // if (i % 5 == 0)
    //      printf " - - - - - - - - - - - - "
    // else
    //      imprimeLinha (i, mapa, pecas);
    //
    // Imprimir '\n'

void imprime (int mat[3][3], listaBolas bolas){
    int i = 1;
    
   // printf(" - - - - - - - - - - - - \n");
    
    for (i = 1; i <= 15; i++) {
        if (i % 5 != 0) {
               // printf(" - - - - - - - - - - - - ");
      //  else 
            
            imprimeLinha (i, mat, bolas);
            printf ("\n");
    
        }
    }
}


int solver(int iter, int mat[3][3], listaBolas bolas) {
    int i, res = 1;
    if (iter == 0) {
        for (i = 0; i < NBOLAS && res; i++){
            if (mat[bolas[i].posy][bolas[i].posx] != bolas[i].cor) {
                res = 0;
            }
        }
        
        if (res) {
            
            /*
            for (res = 0; res < NBOLAS; res++) {
                printf("\n->Bola %d -> (%d, %d) -> %d\n", res, bolas[res].posx, bolas[res].posy, bolas[res].cor);
            }
            */
            return 1;
        }
        
    } else if (solver(iter - 1, mat, direita(mat, bolas))) {
        printf("Direita\n");
        
        /*
        for (res = 0; res < NBOLAS; res++) {
            printf("\n->Bola %d -> (%d, %d) -> %d\n", res, bolas[res].posy, bolas[res].posx, bolas[res].cor);
        }
        */
        return 1;
    
        
    }
    else if (solver(iter - 1, mat, esquerda(mat, bolas))) {
        printf("Esquerda\n");
        return 1;
        
    }
    else if (solver(iter - 1, mat, cima(mat, bolas))) {
        printf("Cima\n");
        return 1;
        
    }
    else if (solver(iter - 1, mat, baixo(mat, bolas))) {
        printf("Baixo\n");
        return 1;
        
    }
    
    free (bolas);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    /*
    int mat[3][3] = {{BLOCO, VERMELHO, BLOCO},
                     {AZUL, VERDE, BLOCO},
                     {LIVRE, LIVRE, LIVRE}};
    
    listaBolas bolas = (listaBolas) malloc(sizeof(struct bolas) * NBOLAS);
    
    bolas[0].posy = 2;
    bolas[0].posx = 0;
    bolas[0].cor = AZUL;
    
    bolas[1].posy = 2;
    bolas[1].posx = 1;
    bolas[1].cor = VERMELHO;
    
    bolas[2].posy = 2;
    bolas[2].posx = 2;
    bolas[2].cor = VERDE;
    */
    
    int mat[3][3] = {{LIVRE, LIVRE, VERDE},
                     {LIVRE, AZUL, BLOCO},
                     {LIVRE, LIVRE, VERMELHO}};
    
    listaBolas bolas = (listaBolas) malloc(sizeof(struct bolas) * NBOLAS);
    
    bolas[0].posy = 0;
    bolas[0].posx = 1;
    bolas[0].cor = VERDE;
    
    bolas[1].posy = 1;
    bolas[1].posx = 0;
    bolas[1].cor = AZUL;
    
    bolas[2].posy = 2;
    bolas[2].posx = 1;
    bolas[2].cor = VERMELHO;
    
    //printf("%d\n", mat[0][1]);
    
    imprime(mat, bolas);
    
    //solver(12, mat, bolas);
    
 //   printf("LER AO CONTRÁRIO\n");
    return 0;
}
