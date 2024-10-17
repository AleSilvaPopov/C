#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

typedef struct{
    unsigned int cdg;
    char nome[100];
    unsigned int idade;
    char sexo;
}Pdados;

//Modulos.
void criar_arquivo();
void cadastrar();
void ver_cadastrados();
void menu();
int vereficar_arv();
void remover_cadastro();
void procura();
void busca(int);

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
                procura();
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
    printf("|\t[?]?????????????????.\t        |\n");
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

    Pdados pessoa;
    char linha[100];

    system("cls");
    printf("Num. Nome\t\t\t\t| Idade Sexo\n");
    printf("-----------------------------------------\n");
    while(fgets(linha, sizeof(linha), aqv) != NULL){
        if(sscanf(linha, "%u %[^0-9] %u %[^\n]c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo) == 4){
            printf("%-4d %-30s\t| %-4d %3c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
        }
    }   
    fclose(aqv);
    system("pause");
}

//Inseri na lista o código, nome e idade da pessoa cadastrada.
void cadastrar(){
    Pdados pessoa;
    char linha[100];
    FILE *aqv;

    pessoa.cdg = 0;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv != NULL){
        while(fgets(linha, sizeof(linha), aqv) != NULL){
            sscanf(linha, "%u", &pessoa.cdg);
        }
        pessoa.cdg += 1;
        fclose(aqv);
    }
    else{
        pessoa.cdg = 1;
    }

    aqv = fopen("ListaUsuarios.txt", "a");
    if(aqv == NULL){
        printf("Erro ao abrir arquivo.\n");
        Sleep(2000);
        return;
    }
    fflush(stdin);
    printf("\nNome: ");
    fgets(pessoa.nome, sizeof(pessoa.nome), stdin);
    pessoa.nome[strcspn(pessoa.nome, "\n")] = 0;

    printf("Idade: ");
    scanf("%u", &pessoa.idade);

    printf("Sexo[M/F]");
    scanf(" %c", &pessoa.sexo);

    fprintf(aqv, "%d %s %d %c\n",pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);


    printf("[%d %s %d %c] --> adicionado com sucesso.", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
    
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
    Pdados pessoa;
    char linha[100];
    unsigned int remover;

    ver_cadastrados();

    printf("Digite o código de quem deseja remover da lista: ");
    scanf("%u", &remover);

    FILE *a, *b;
    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro, ao abrir o arquivo .txt.\n");
        return;
    }
    b = fopen("temp.txt", "w");
    if(b == NULL){
        printf("Erro, ao abrir o arquivo temporario .txt.\n");
        fclose(a);
        return;
    }

    while(fgets(linha, sizeof(linha), a) != NULL){
        sscanf(linha, "%u %[^0-9] %u %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
        if(remover != pessoa.cdg){
             fprintf(b, "%u %s%u %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
         }
    }
    fclose(a);
    fclose(b);

    remove("ListaUsuarios.txt");
    rename("temp.txt", "ListaUsuarios.txt");

    printf("Cadastro removido com sucesso.\n");
    system("PAUSE");
}

void procura(){

    unsigned int escolha;

    do{
        system("cls");
        printf("\tO que deseja procurar: \n");
        printf("\t[1] Femininos.\n\t[2] Masculinos.\n\t[3] Código\n\t[4] Idade\n\t[5] Sair\n");
        printf("\tSua esolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            //Buscar todos do sexo Feminino.
            system("cls");
            busca(1);
            break;
        case 2:
            //Buscar todos do sexo Masculino.
            system("cls");
            busca(2);
            break;
        case 3:
            //Buscar uma unica pessoa com o codigo informado.
            system("cls");
            busca(3);
            break;
        case 4:
            //Buscar todos com a idade informada.
            system("cls");
            busca(4);
            break;
        case 5:
            system("cls");
            printf("Voltando pro menu principal.\n");
            Sleep(1000);
            break;
        
        default:
            system("cls");
            printf("Erro, tente novamente em 2 segundos\n");
            Sleep(2000);
            break;
        }
    }while(escolha != 5);
}

void busca(int n){
    FILE *a;
    char linha[100];
    Pdados pessoa;
    unsigned int cdg, flag = 0;

    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro!\n");
        return;
    }
    else{
        if(n == 1){
            //Busca Feminina
            printf("\n");
            while(fgets(linha, sizeof(linha), a) != NULL){
                sscanf(linha, "%u %[^0-9] %d %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
                if(pessoa.sexo == 'F' || pessoa.sexo == 'f'){
                    if(flag == 0){
                        printf("Mulheres encontradas: \n");
                        flag++;
                    }
                    printf("%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                }
            }
            if(flag == 0){
                printf("Nenhuma mulher encontrada.\n");
            }
            system("PAUSE");
        }
        if(n == 2){
            //Busca Masculina
            while(fgets(linha, sizeof(linha), a) != NULL){
                sscanf(linha, "%u %[^0-9] %d %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
                if(pessoa.sexo == 'M' || pessoa.sexo == 'm'){
                    if(flag == 0){
                        printf("Homens encontrados: \n");
                        flag++;
                    }
                    printf("%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                }   
            }
            if(flag == 0){
                printf("Nenhum homem encontrado.\n");
            }
            system("pause");
        }
        if(n == 3){
            printf("Informe o codigo: ");
            scanf("%u", &cdg);
            while(fgets(linha, sizeof(linha), a) != NULL){
                sscanf(linha, "%u %[^0-9] %u %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
                if(pessoa.cdg == cdg){
                    flag++;
                    printf("Usuario: %d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                }
            }
            if(flag == 0){
                printf("Cadastro não encontrado.\n");
            }
            system("PAUSE");
        }
        if(n == 4){
             printf("Informe a idade: ");
            scanf("%u", &cdg);
            while(fgets(linha, sizeof(linha), a) != NULL){
                sscanf(linha, "%u %[^0-9] %d %c", &pessoa.cdg, pessoa.nome, &pessoa.idade, &pessoa.sexo);
                if(pessoa.idade == cdg){
                    if(flag == 0){
                        printf("Pessoas de %u anos encontradas: \n", cdg);
                    }
                    flag++;
                    printf("%d %s %d %c\n", pessoa.cdg, pessoa.nome, pessoa.idade, pessoa.sexo);
                }
            }
            if(flag == 0){
                printf("Ninguem com essa idade foi encontrado.\n");
            }
            system("PAUSE");
        }
    }
}
