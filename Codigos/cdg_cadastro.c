#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

//Modulos.
void criar_arquivo();
void cadastrar();
void ver_cadastrados();
void menu();
int vereficar_arv();
void remover_cadastro();

int main(){
    setlocale(LC_ALL, "Portuguese"); // Deixar em Português.
    int escolha; // Variavel para a escolha do usuário.
    
    // verificar se já existe um arquivo .txt se não existir cria um.
    if(vereficar_arv() == 1){
        criar_arquivo();
    }
    else{
        printf("-->Arquivo já existe.\n");
        Sleep(2000);
    }

    do{
        system("cls"); // apaga tudo no terminar.
        menu(); 
        escolha = getche(); // lê a escolha do usuário, getche lê tabela ASCII.
        //Acessa a escolha.
        switch (escolha){
            case '1':
                // Cadastra novo nome na lista.
                cadastrar();
                break;
            case '2':
                // Imprime a lista.
                ver_cadastrados();
                break;
            case '3':
                //Remove nome da lista
                remover_cadastro();
                break;
            case '4':
                //Procura na lista, de acordo com a escolha do usuário(Ex: Um nome, Sexo, Idade etc.)
                break;
            case '5':
            //Finaliza o código.
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
                //Tratamento de erro caso o usuário digite algo inválido.
                printf("\n\tErro ao digitar.\n\tEspere três segundos e tente novamente.\n");
                Sleep(3000);
                break;
        }
    } while(escolha != '5'); //Se escolha for diferente de 5 ele continua o programa.

    return 0;
}

//Menu com todas as opções.
void menu(){
    printf("-----------------------------------------");
    printf("\n|\t    Menu Principal\t        |\n");
    printf("-----------------------------------------");
    printf("\n|\t[1]Adicionar nome a lista.\t|\n");
    printf("|\t[2]Ver lista.\t                |\n");
    printf("|\t[3]Tirar nome da lista\t        |\n");
    printf("|\t[4]Procurar na lista.\t        |\n");
    printf("|\t[5]Sair do programa.\t        |\n");
    printf("-----------------------------------------");
    printf("\n\tDigite sua escolha: ");
}

//Cria arquivo caso ele não exista.
void criar_arquivo(){

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

//Imprime todas as pessoas já cadastradas.
void ver_cadastrados(){
    FILE *aqv;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv == NULL){
        printf("\nErro ao abrir arquivo para leitura.\n");
        Sleep(2000);
        return;
    }

    unsigned int idade, cdg = 0;
    char nome[50], linha[100], sexo;

    system("cls");
    printf("Num. Nome\t\t\t\t| Idade Sexo\n");
    printf("-----------------------------------------\n");
    while(fgets(linha, sizeof(linha), aqv) != NULL){
        if(sscanf(linha, "%u %[^0-9] %u %[^\n]c", &cdg, nome, &idade, &sexo) == 4){
            printf("%-4d %-30s\t| %-3d %2c\n", cdg, nome, idade, sexo);
        }
        
    }   
    fclose(aqv);
    system("pause");
}

//Inseri na lista o código, nome e idade da pessoa cadastrada.
void cadastrar(){
    unsigned int idade, cdg = 0;
    char sexo, nome[100], linha[100];
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

    printf("Sexo[M/F]");
    scanf(" %c", &sexo);

    fprintf(aqv, "%d %s %d %c\n",cdg, nome, idade, sexo);


    printf("[%d %s %d %c] --> adicionado com sucesso.", cdg, nome, idade, sexo);
    
    fclose(aqv);
    system("PAUSE");
}

//Verifica se o arquivo já existe para se não poder criar um novo.
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

//Remove uma pessoa indesejada da lista.
void remover_cadastro(){
    unsigned int remover, idade, cdg;
    char linha[100], nome[50], sexo;

    ver_cadastrados();

    printf("Digite o código de quem deseja remover da lista: ");
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
        sscanf(linha, "%u %[^0-9] %u %c", &cdg, nome, &idade, &sexo);
        if(remover != cdg){
             fprintf(b, "%d %s %d %c\n", cdg, nome, idade, sexo);
         }
    }
    fclose(a);
    fclose(b);

    remove("ListaUsuarios.txt");
    rename("temp.txt", "ListaUsuarios.txt");

    printf("Cadastro removido com sucesso.\n");
    system("PAUSE");
}
