//
//  main.c
//  Strassen
//
//  Created by José Luiz Junior on 23/09/20.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct t_pixel{
    int r, g, b;
} pixel;

void print_matrix(int n, pixel ** M){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d %d %d ", M[i][j].r, M[i][j].g, M[i][j].b);
        }
        printf("\n");
    }
}

void boring_multi(int n, pixel ** X, pixel ** Y, pixel ** Z){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int res_r = 0, res_g = 0, res_b = 0;
            //imagem linha i * filtro coluna j
            for(int k = 0; k < n; k++){
                res_r += X[i][k].r * Y[k][j].r;
                res_g += X[i][k].g * Y[k][j].g;
                res_b += X[i][k].b * Y[k][j].b;
            }
            Z[i][j].r = res_r;
            Z[i][j].g = res_g;
            Z[i][j].b = res_b;
        }
    }
}


// Recebe tamanho n da matriz X (nxn) e Y (nxn) e resultado Z (nxn)
void strassen_multi(int n, pixel ** X, pixel ** Y, pixel ** Z){


}


// n = tamanho da matriz resultado que eh a Z que tem dimensao nxn
// X e Y tambem tem dimensao nxn
void soma_mat(int n, pixel ** X, pixel ** Y, pixel ** Z){
    
    // Lembrar de somar os RGB e nao os itens
    
    
}

// n = tamanho da matriz resultado (que vai ser o dobro de R,S,T,U, que sao (n/2)x(n/2))
// Matriz resultado = F de dimensao nxn
void junta_mat(int n, pixel ** R, pixel ** S, pixel ** T, pixel ** U, pixel ** F){
    
    
    
    
}

// Matriz entrada = E que tem dimensao nxn
// P1 (n/2 x n/2) recebe A|E
// P2 (n/2 x n/2) recebe B|F
// P3 (n/2 x n/2) recebe C|G
// P4 (n/2 x n/2) recebe D|H
void parte_mat(int n, pixel ** E, pixel ** P1, pixel ** P2, pixel ** P3, pixel ** P4, pixel ** P5){
    
    
    
    
}


int main(int argc, const char* argv[]){
    int n, aux_i;
    char aux;

    pixel ** imagem;
    pixel ** filtro;
    pixel ** resultado;

    scanf("%c%d", &aux, &aux_i);
    getchar();
    scanf("%d %d", &n, &aux_i);
    scanf("%d", &aux_i);

    //Vou considerar que imagem[i][j] é o pixel da linha i e coluna j
    //note que essa convenção é arbitrária mas uma vez que eu assumi isso
    //devo tomar cuidado para não trocar
    imagem = (pixel **) malloc(n * sizeof(pixel *));
    filtro = (pixel **) malloc(n * sizeof(pixel *));
    resultado = (pixel **) malloc(n * sizeof(pixel *));
    for(int i = 0; i < n; i++){
        imagem[i] = (pixel *) malloc(n * sizeof(pixel));
        filtro[i] = (pixel *) malloc(n * sizeof(pixel));
        resultado[i] = (pixel *) malloc(n * sizeof(pixel));
    }

    //cuidado, aqui vou ler linha a linha
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d %d %d", &(imagem[i][j].r), &(imagem[i][j].g), &(imagem[i][j].b));
        }
    }

    //lendo linha a linha do filtro
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d %d %d", &(filtro[i][j].r), &(filtro[i][j].g), &(filtro[i][j].b));
        }
    }


    boring_multi(n, imagem, filtro, resultado);
    //strassen_multi(n, imagem, filtro, resultado);

    printf("P3\n%d %d\n255\n", n, n);
    print_matrix(n, resultado);


    return 0;
}
