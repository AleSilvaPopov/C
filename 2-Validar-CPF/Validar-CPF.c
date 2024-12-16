#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct{
    int dgt[9];
    int DVs[2];
}CPF;

CPF* ler_CPF();
int DV1(CPF*);
int DV2(CPF*);
int DVF(int);

int main(){
    CPF *ptr;
    ptr = ler_CPF();

    if(ptr->DVs[0] == DV1(ptr) && ptr->DVs[1] == DV2(ptr)){
        printf("\nCPF valido.\n");
    }
    else{
        printf("\nCPF invalido.\n");
    }

    return 0;
}

CPF* ler_CPF(){
    CPF *ptr = malloc(sizeof(CPF));
    int i;

    printf("Informe seu CPF: ");
    for(i=0; i<9; i++){
        //scanf("%1d", &ptr->dgt[i]);
        ptr->dgt[i] = getche() - '0';
        if(i == 2 || i == 5){
            printf(".");
        }
    }
    for(i=0; i<2; i++){
        //scanf("%1d", &ptr->DVs[i]);
        if(i == 0){
            printf("-");
        }
        ptr->DVs[i] = getche() - '0';
    }
    return ptr;
}

int DV1(CPF *ptr){//406.947.548-62
    int i, j, soma = 0;
    CPF *temp = malloc(sizeof(CPF));

    for(i = 10, j=0; i>1 && j<9; i--, j++){
        temp->dgt[j] = ptr->dgt[j] * i;
        soma = soma + temp->dgt[j];
    }
    free(temp);
    return DVF(soma);
}

int DV2(CPF *ptr){
    int i, j, soma = 0;
    CPF *temp = malloc(sizeof(CPF));
    for(i = 11, j=0; i>2 && j<9; i--, j++){
        temp->dgt[j] = ptr->dgt[j] * i;
        soma = soma + temp->dgt[j];
    }
    soma = soma + (ptr->DVs[0] * 2); //DV1(ptr) * 2;
    free(temp);
    return DVF(soma);
}

int DVF(int s){
    if(s % 11 < 2){
        return 0;
    }
    else{
        return 11 - s % 11;
    }
}