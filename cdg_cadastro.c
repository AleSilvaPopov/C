#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

void criar_arquivo();
void cadastrar();
void ver_cadastrados();
void menu();
int vereficar_arv();
void remover_cadastro();

int main(){
    setlocale(LC_ALL, "Portuguese");
    int escolha;
    
    if(vereficar_arv() == 1){
        criar_arquivo();
    }
    else{
        printf("-->Arquivo já existe.\n");
        Sleep(2000);
    }
    do{
        system("cls");
        menu();
        escolha = getche();
        switch (escolha){
            case '1':
                // adicionar nome ao arquivo.
                cadastrar();
                break;
            case '2':
                // Ver lista.
                ver_cadastrados();
                break;
            case '3':
                //Tirar nome da lista
                remover_cadastro();
                break;
            case '4':
                system("cls");
                printf("fi");
                Sleep(500);
                printf("na");
                Sleep(500);
                printf("li");
                Sleep(500);
                printf("zan");
                Sleep(500);
                printf("do");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".");
                Sleep(500);
                printf(".\n");
                Sleep(200);
                break;
            default:
                printf("\n\tErro ao digitar.\n\tEspere três segundos e tente novamente.\n");
                Sleep(3000);
                break;
        }
    } while(escolha != '4');

    return 0;
}

void menu(){
    printf("-----------------------------------------");
    printf("\n|\t    Menu Principal\t        |\n");
    printf("-----------------------------------------");
    printf("\n|\t[1]Adicionar nome a lista.\t|\n");
    printf("|\t[2]Ver lista.\t                |\n");
    printf("|\t[3]Tirar nome da lista\t        |\n");
    printf("|\t[4]Sair do programa.\t        |\n");
    printf("-----------------------------------------");
    printf("\n\tDigite sua escolha: ");
}

void criar_arquivo(){

    //C:\Users\alexa\OneDrive\Área de Trabalho\Códigos

    FILE *aqv;
    aqv = fopen("ListaUsuarios.txt", "w");
    if(aqv == NULL){
        printf("\nErro ao abrir o arquivo.\n");
        Sleep(2000);
        return;
    }
    else{
        printf("\nSucesso ao abrir o arquivo.\n");
        Sleep(2000);
    }

    fclose(aqv);
}

void ver_cadastrados(){
    FILE *aqv;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv == NULL){
        printf("\nErro ao abrir arquivo para leitura.\n");
        Sleep(2000);
        return;
    }

    unsigned int idade, cdg = 0;
    char nome[50];
    char linha[100];

    system("cls");
    printf("Num. Nome\t\t\t\t| Idade\n");
    printf("-----------------------------------------\n");
    while(fgets(linha, sizeof(linha), aqv) != NULL){
        if(sscanf(linha, "%u %[^0-9] %u", &cdg, nome, &idade) == 3){
            printf("%-4d %-30s\t| %3d\n", cdg, nome, idade);
        }
        
    }   
    fclose(aqv);
    system("pause");
}

void cadastrar(){
    unsigned int idade, cdg = 0;
    char nome[100], linha[100];
    FILE *aqv;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv != NULL){
        while(fgets(linha, sizeof(linha), aqv) != NULL){
            sscanf(linha, "%u", &cdg);
        }
        cdg += 1;
        fclose(aqv);
    }
    else{
        cdg = 1;
    }

    aqv = fopen("ListaUsuarios.txt", "a");
    if(aqv == NULL){
        printf("Erro ao abrir arquivo.\n");
        Sleep(2000);
        return;
    }
    fflush(stdin);
    printf("\nNome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Idade: ");
    scanf("%u", &idade);

    fprintf(aqv, "%d %s %d\n",cdg, nome, idade);

    printf("[%d %s %d] --> adicionado com sucesso.", cdg, nome, idade);
    
    fclose(aqv);
    system("PAUSE");
}

int vereficar_arv(){
    FILE *a;
    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        fclose(a);
        return 1;
    }
    else{
        fclose(a);
        return 0;
    }
}

void remover_cadastro(){
    unsigned int remover, idade, cdg;
    char linha[100], nome[50];

    ver_cadastrados();

    printf("Digite o cogido de quem deseja remover da lista: ");
    scanf("%u", &remover);

    FILE *a, *b;
    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro, ao abrir o arquivo.txt.\n");
        return;
    }
    b = fopen("temp.txt", "w");
    if(b == NULL){
        printf("Erro, ao abrir o arquivo temporario .txt.\n");
        fclose(a);
        return;
    }

    while(fgets(linha, sizeof(linha), a) != NULL){
        sscanf(linha, "%u %[^0-9] %u", &cdg, nome, &idade);
        if(remover != cdg){
             fprintf(b, "%d %s %d\n", cdg, nome, idade);
         }
    }
    fclose(a);
    fclose(b);

    remove("ListaUsuarios.txt");
    rename("temp.txt", "ListaUsuarios.txt");

    printf("Cadastro removido com sucesso.\n");
    system("PAUSE");
}