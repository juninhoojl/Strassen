//
//  main.c
//  Strassen
//
//  Created by José Luiz Junior on 23/09/20.
//  Disciplina: CIC110 - Análise e Projeto de Algoritmos I
//  Grupo: José Luiz Junior e Isabela Corsi


#include <stdio.h>
#include <stdlib.h>

typedef struct t_pixel{
    int r, g, b;
} pixel;

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
            P2[i][j-(n/2)].r = E[i][j].r;
            P2[i][j-(n/2)].g = E[i][j].g;
            P2[i][j-(n/2)].b = E[i][j].b;
        }
    }
    
    for(int i = n/2; i < n; i++){ // Segunda metade das linhas
        for(int j = 0; j < n/2; j++){ // Primeira metade das colunas P2
            P3[i-(n/2)][j].r = E[i][j].r;
            P3[i-(n/2)][j].g = E[i][j].g;
            P3[i-(n/2)][j].b = E[i][j].b;
        }
        for(int j = n/2; j < n; j++){ // Segunda metade das colunas P2
            P4[i-(n/2)][j-(n/2)].r = E[i][j].r;
            P4[i-(n/2)][j-(n/2)].g = E[i][j].g;
            P4[i-(n/2)][j-(n/2)].b = E[i][j].b;
        }
    }
    
}

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

// n = tamanho da matriz resultado que eh a Z que tem dimensao nxn
// X e Y tambem tem dimensao nxn
void soma_mat(int n, pixel ** X, pixel ** Y){
    
    // Lembrar de somar os RGB e nao os itens
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            X[i][j].r += Y[i][j].r;
            X[i][j].g += Y[i][j].g;
            X[i][j].b += Y[i][j].b;
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

// Recebe tamanho n da matriz X (nxn) e Y (nxn) e resultado Z (nxn)
void strassen_multi(int n, pixel ** X, pixel ** Y, pixel ** Z){

    // Confere caso base, deixar 32 no futuro
    if(n <= 32){
        boring_multi(n, X, Y, Z);
        return;
    }

    // Aloca as matrizes para partir
    pixel ** A = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** B = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** C = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** D = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** E = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** F = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** G = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** H = (pixel **) malloc(n/2 * sizeof(pixel *));
    
    pixel ** AE = (pixel **) malloc(n/2 * sizeof(pixel *)); // Vai virar R = AE + BG
    pixel ** BG = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** AF = (pixel **) malloc(n/2 * sizeof(pixel *)); // Vai virar S = AF + BH
    pixel ** BH = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** CE = (pixel **) malloc(n/2 * sizeof(pixel *)); // Vai virar T = CE + DG
    pixel ** DG = (pixel **) malloc(n/2 * sizeof(pixel *));
    pixel ** CF = (pixel **) malloc(n/2 * sizeof(pixel *)); // Vai virar U = CF + DH
    pixel ** DH = (pixel **) malloc(n/2 * sizeof(pixel *));

    for(int i = 0; i < n/2; i++){
        A[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        B[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        C[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        D[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        E[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        F[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        G[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        H[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        AE[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        BG[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        AF[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        BH[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        CE[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        DG[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        CF[i] = (pixel *) malloc(n/2 * sizeof(pixel));
        DH[i] = (pixel *) malloc(n/2 * sizeof(pixel));
    }
    
    parte_mat(n, X, A, B, C, D);
    parte_mat(n, Y, E, F, G, H);
    
    strassen_multi(n/2, A, E, AE);
    strassen_multi(n/2, B, G, BG);
    soma_mat(n/2, AE, BG);
    
    strassen_multi(n/2, A, F, AF);
    strassen_multi(n/2, B, H, BH);
    soma_mat(n/2, AF, BH);
    
    strassen_multi(n/2, C, E, CE);
    strassen_multi(n/2, D, G, DG);
    soma_mat(n/2, CE, DG);
    
    strassen_multi(n/2, C, F, CF);
    strassen_multi(n/2, D, H, DH);
    soma_mat(n/2, CF, DH);
    
    junta_mat(n, AE, AF, CE, CF, Z);

    free(A);
    free(B);
    free(C);
    free(D);
    free(E);
    free(F);
    free(G);
    free(H);
    free(AE);
    free(BG);
    free(AF);
    free(BH);
    free(CE);
    free(DG);
    free(CF);
    free(DH);
    return;
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
    strassen_multi(n, imagem, filtro, resultado);
    printf("P3\n%d %d\n255\n", n, n);
    print_matrix(n, resultado);
    free(imagem);
    free(filtro);
    free(resultado);
    return 0;
}
