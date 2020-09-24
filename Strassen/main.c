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
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Z[i][j].r = X[i][j].r + Y[i][j].r;
            Z[i][j].g = X[i][j].g + Y[i][j].g;
            Z[i][j].b = X[i][j].b + Y[i][j].b;
        }
    }
}

// n = tamanho da matriz resultado (que vai ser o dobro de R,S,T,U, que sao (n/2)x(n/2))
// Matriz resultado = F de dimensao nxn
void junta_mat(int n, pixel ** R, pixel ** S, pixel ** T, pixel ** U, pixel ** F){
    
    for(int i = 0; i < n/2; i++){ // Primeira metade das linhas
        for(int j = 0; j < n/2; j++){ // Primeira metade das colunas P1
            F[i][j].r = R[i][j].r;
            F[i][j].g = R[i][j].g;
            F[i][j].b = R[i][j].b;
        }
        for(int j = n/2; j < n; j++){ // Segunda metade das colunas P1
            F[i][j].r = S[i][j-n/2].r;
            F[i][j].g = S[i][j-n/2].g;
            F[i][j].b = S[i][j-n/2].b;
        }
    }
    
    for(int i = n/2; i < n; i++){ // Segunda metade das linhas
        for(int j = 0; j < n/2; j++){ // Primeira metade das colunas P2
            F[i][j].r = T[i-n/2][j].r;
            F[i][j].g = T[i-n/2][j].g;
            F[i][j].b = T[i-n/2][j].b;
        }
        for(int j = n/2; j < n; j++){ // Segunda metade das colunas P2
            F[i][j].r = U[i-n/2][j-n/2].r;
            F[i][j].g = U[i-n/2][j-n/2].g;
            F[i][j].b = U[i-n/2][j-n/2].b;
        }
    }
    
    
    
}

// Matriz entrada = E que tem dimensao nxn
// P1 (n/2 x n/2) recebe A|E
// P2 (n/2 x n/2) recebe B|F
// P3 (n/2 x n/2) recebe C|G
// P4 (n/2 x n/2) recebe D|H
void parte_mat(int n, pixel ** E, pixel ** P1, pixel ** P2, pixel ** P3, pixel ** P4){
    
    for(int i = 0; i < n/2; i++){ // Primeira metade das linhas
        for(int j = 0; j < n/2; j++){ // Primeira metade das colunas P1
            P1[i][j].r = E[i][j].r;
            P1[i][j].g = E[i][j].g;
            P1[i][j].b = E[i][j].b;
        }
        for(int j = n/2; j < n; j++){ // Segunda metade das colunas P1
            P2[i][j-n/2].r = E[i][j].r;
            P2[i][j-n/2].g = E[i][j].g;
            P2[i][j-n/2].b = E[i][j].b;
        }
    }
    
    for(int i = n/2; i < n; i++){ // Segunda metade das linhas
        for(int j = 0; j < n/2; j++){ // Primeira metade das colunas P2
            P3[i-n/2][j].r = E[i][j].r;
            P3[i-n/2][j].g = E[i][j].g;
            P3[i-n/2][j].b = E[i][j].b;
        }
        for(int j = n/2; j < n; j++){ // Segunda metade das colunas P2
            P4[i-n/2][j-n/2].r = E[i][j].r;
            P4[i-n/2][j-n/2].g = E[i][j].g;
            P4[i-n/2][j-n/2].b = E[i][j].b;
        }
    }
    
}


int main(int argc, const char* argv[]){
    int n, aux_i;
    char aux;
    
    scanf("%c%d", &aux, &aux_i);
    getchar();
    scanf("%d %d", &n, &aux_i);
    scanf("%d", &aux_i);

    //Vou considerar que imagem[i][j] é o pixel da linha i e coluna j
    //note que essa convenção é arbitrária mas uma vez que eu assumi isso
    //devo tomar cuidado para não trocar
    pixel ** imagem = (pixel **) malloc(n * sizeof(pixel *));
    pixel ** filtro = (pixel **) malloc(n * sizeof(pixel *));
    pixel ** resultado = (pixel **) malloc(n * sizeof(pixel *));
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

    // Teste soma ok
    /*
    pixel ** soma = (pixel **) malloc(n * sizeof(pixel *));
    for(int i = 0; i < n; i++){
        soma[i] = (pixel *) malloc(n * sizeof(pixel));
    }

    soma_mat(n, imagem, imagem, soma);
    printf("\n\n\n\n");
    print_matrix(n, soma);
    printf("\n\n\n\n");
    return 0;
    */
    
    // Teste parte ok
    
    /*
    pixel ** R = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** S = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** T = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** U = (pixel **) malloc(n/2 * sizeof(pixel *));
    for(int i = 0; i < n/2; i++){
        R[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        S[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        T[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        U[i] = (pixel *) malloc(n/2 * sizeof(pixel));
    }
    
    parte_mat(n, imagem, R, S, T, U);
    printf("\n\n\n\n");
    print_matrix(n/2, R);
    printf("\n\n\n\n");
    print_matrix(n/2, S);
    printf("\n\n\n\n");
    print_matrix(n/2, T);
    printf("\n\n\n\n");
    print_matrix(n/2, U);
    printf("\n\n\n\n");

    // Testa juntar matrizes
    pixel ** junta = (pixel **) malloc(n * sizeof(pixel *));
    for(int i = 0; i < n; i++){
        junta[i] = (pixel *) malloc(n * sizeof(pixel));
    }
    
    junta_mat(n, R, S, T, U, junta);
    
    
    printf("\n\n\n\n");
    print_matrix(n, junta);
    printf("\n\n\n\n");
     
    */
    
    boring_multi(n, imagem, filtro, resultado);
    
    
    
    //strassen_multi(n, imagem, filtro, resultado);

    printf("P3\n%d %d\n255\n", n, n);
    print_matrix(n, resultado);


    return 0;
}
