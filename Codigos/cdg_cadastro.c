#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

typedef struct{
    int dia;
    int mes;
    int ano;
}data;

typedef struct{
    unsigned int cdg;
    char nome[100];
    unsigned int idade;
    char sexo;
    data Dnasc;
}Pdados;

//Modulos.
void criar_arquivo();
Pdados* ler_novo_cadastro();
void cadastrar();
void ver_cadastrados();
void menu(int);
int vereficar_arv();
void remover_cadastro();
void procura();
unsigned int busca(int);
void erro();
void novo_arquivo(int, unsigned int);

int main(){
    setlocale(LC_ALL, "Portuguese"); // Deixar em Português.
    int escolha; // Variavel para a escolha do usuário.
    Pdados *pessoa;
    
    // verificar se já existe um arquivo .txt se não existir cria um.
    if(vereficar_arv() == 1){
        criar_arquivo();
    }
    else{
        printf("|Arquivo já existe.|\n");
        Sleep(1000);
    }

    do{
        system("cls");
        menu(1); 
        escolha = getche(); // lê a escolha do usuário, getche lê tabela ASCII.
        //Acessa a escolha.
        switch (escolha){
            case '1':
                pessoa = ler_novo_cadastro();
                cadastrar(pessoa); // Cadastra novo nome na lista.
                break;
            case '2':
                ver_cadastrados(); // Imprime a lista.
                break;
            case '3':
                remover_cadastro(); //Remove nome da lista.
                break;
            case '4':
                procura(); //Procura na lista, de acordo com a escolha do usuário(Ex: Um nome, Sexo, Idade etc.)
                break;
            case '5':
                //??????
                break;
            case '6':
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
                erro();
                break;
        }
    } while(escolha != '6'); //Se escolha for diferente de 6 ele continua o programa.

    return 0;
}

//Menu com todas as opções.
void menu(int n){
    if(n == 1){
        printf("-----------------------------------------");
    printf("\n|\t    Menu Principal\t        |\n");
    printf("-----------------------------------------");
    printf("\n|\t[1]Adicionar nome a lista.\t|\n");
    printf("|\t[2]Ver lista.\t                |\n");
    printf("|\t[3]Tirar nome da lista\t        |\n");
    printf("|\t[4]Procurar na lista.\t        |\n");
    printf("|\t[5]?????????????????.\t        |\n");
    printf("|\t[6]Sair do programa.\t        |\n");
    printf("-----------------------------------------");
    printf("\n\tDigite sua escolha: ");

    }
    if(n == 2){
        system("cls");
        printf("\tO que deseja procurar: \n");
        printf("\t[1] Femininos.\n\t[2] Masculinos.\n\t[3] Código\n\t[4] Idade\n\t[5] Voltar\n");
        printf("\tSua esolha: ");
    }
}

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

void ver_cadastrados(){
    /*
        Não recebe escopo.
        Mostra uma lista com todos os dados cadastrados.
    */
    FILE *aqv;

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv == NULL){
        printf("\nErro ao abrir arquivo para leitura.\n");
        Sleep(2000);
        return;
    }

    Pdados *p;
    p = malloc(sizeof(Pdados));
    char linha[150];

    system("cls");
    printf("Num. Nome\t\t\t\t| Idade | Sexo | Data de Nasc.|\n");
    printf("-----------------------------------------------------------------------\n");
    while(fgets(linha, sizeof(linha), aqv) != NULL){
        if(sscanf(linha, "%u %[^0-9] %u %c %2d %2d %4d", &p->cdg, p->nome, &p->idade, &p->sexo, &p->Dnasc.dia, &p->Dnasc.mes, &p->Dnasc.ano) == 7){
            printf("%-4d %-30s\t| %4d  |%3c   | %2d/%2d/%4d   |\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
        }
    }
    free(p);
    fclose(aqv);
    system("pause");
}

int vereficar_arv(){
    /*
        Não recebe escopo.
        Verifica se já existe um arquivo com dados salvos.
     */
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

Pdados* ler_novo_cadastro(){
    Pdados *p;
    p = malloc(sizeof(Pdados));

    if(p){
        getchar();
        printf("\nNome:");
        scanf("%[^\n]s", p->nome);
        printf("Idade: ");
        scanf("%u", &p->idade);
        printf("Sexo[M/F]: ");
        scanf(" %c", &p->sexo);
        printf("Ano de nascimento[dd mm aaaa]: ");
        scanf("%2d %2d %4d", &p->Dnasc.dia, &p->Dnasc.mes, &p->Dnasc.ano);
        return p;
    }
    else{
        printf("\n\tErro em alocar a memoria.\n");
        return NULL;
    }
}

void cadastrar(Pdados *p){
    char linha[100];
    FILE *aqv;

    p->cdg = 0;

    system("cls");

    aqv = fopen("ListaUsuarios.txt", "r");
    if(aqv != NULL){
        while(fgets(linha, sizeof(linha), aqv) != NULL){
            sscanf(linha, "%u", &p->cdg);
        }
        p->cdg += 1;
        fclose(aqv);
    }
    else{
        p->cdg = 1;
    }

    aqv = fopen("ListaUsuarios.txt", "a");
    if(aqv == NULL){
        printf("Erro ao abrir arquivo.\n");
        erro();
        return;
    }
    fflush(stdin);
    fprintf(aqv, "%d %s %d %c %2d %2d %4d\n",p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
    printf("Codigo: %d\nNome: %s\nIdade: %d\nSexo: %c\nData de nascimento: %2d/%2d/%4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
    printf(" --> Dados adicionados com sucesso.<--");
    
    free(p);
    fclose(aqv);
    system("PAUSE");
}

void remover_cadastro(){
    /*
        Não receve escopo.
        Remove um certo dado da lista de acordo com a escolha do usuário.
    */
    Pdados *p;
    char linha[150];
    unsigned int remover;

    p = malloc(sizeof(Pdados));
    if(p == NULL){
        erro();
        return;
    }

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
        sscanf(linha, "%u %[^0-9] %u %c %2d %2d %4d", &p->cdg, p->nome, &p->idade, &p->sexo, &p->Dnasc.dia, &p->Dnasc.mes, &p->Dnasc.ano);
        if(remover != p->cdg){
             fprintf(b, "%u %s%u %c %2d %2d %4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
         }
    }
    fclose(a);
    fclose(b);

    remove("ListaUsuarios.txt");
    rename("temp.txt", "ListaUsuarios.txt");

    printf("Cadastro removido com sucesso.\n");
    free(p);
    system("PAUSE");
}

void procura(){
    /*
        Da novas opçôes de busca para o usuário.
    */
    unsigned int escolha, r;
    char Narq;

    do{
        menu(2);
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            //Buscar todos do sexo Feminino.
            system("cls");
            r = busca(1);
            break;
        case 2:
            //Buscar todos do sexo Masculino.
            system("cls");
            r = busca(2);
            break;
        case 3:
            //Buscar uma unica pessoa com o codigo informado.
            system("cls");
            r = busca(3);
            break;
        case 4:
            //Buscar todos com a idade informada.
            system("cls");
            r = busca(4);
            break;
        case 5:
            system("cls");
            printf("Voltando pro menu principal.\n");
            Sleep(1000);
            break;
        
        default:
            erro();
            break;
        }
        if(escolha != 5 && escolha != 3){
            printf("Deseja um arquivo com essa lista:[S/N]: ");
            scanf(" %c", &Narq);
            if(Narq == 'S' || Narq == 's'){
            novo_arquivo(escolha, r);
            }
        }
    }while(escolha != 5);

}

unsigned int busca(int n){
    /*
        Busca algo na lista de acordo com a escolha do usuario.
    */
    FILE *a;
    char linha[100];
    Pdados *p;
    p = malloc(sizeof(Pdados));
    unsigned int cdg, flag = 0, flag2 = 0;

    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro!\n");
        return 1;
    }
    else{
        while(fgets(linha, sizeof(linha), a) != NULL){
            sscanf(linha, "%u %[^0-9] %d %c %2d %2d %4d", &p->cdg, p->nome, &p->idade, &p->sexo, &p->Dnasc.dia, &p->Dnasc.mes, &p->Dnasc.ano);
            if(n == 1){
            //Busca Feminina
                if(p->sexo == 'F' || p->sexo == 'f'){
                    if(flag2 == 0){
                        printf("Mulheres encontradas: \n");
                        flag2++;
                    }
                    printf("%d %s %d %c %2d/%2d/%4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                    flag++;
                }
            }
            if(n == 2){
                //Busca Masculina
                if(p->sexo == 'M' || p->sexo == 'm'){
                    if(flag2 == 0){
                        printf("Homens encontrados: \n");
                        flag2++;
                    }
                        printf("%d %s %d %c %2d/%2d/%4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                        flag++;
                }
            }
            if(n == 3){
                //Busca pelo codigo.
                if(flag2 == 0){
                    printf("Informe o codigo: ");
                    scanf("%u", &cdg);
                    flag2++;
                }
                if(p->cdg == cdg){
                    printf("Usuario: %d %s %d %c %2d/%2d/%4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                    flag++;
                }
            }
            if(n == 4){
                //Busca pela Idade.
                if(flag2 == 0){
                    printf("Informe a idade: ");
                    scanf("%u", &cdg);
                    flag2++;
                }
                if(p->idade == cdg){
                    if(flag == 0){
                        printf("Pessoas de %u anos encontradas: \n", cdg);
                        flag++;
                    }
                    printf("Codigo: %d | Nome --> %s | Sexo --> %c | Aniversario: %2d %2d %4d\n", p->cdg, p->nome, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                }
            }
        }
    }
    if(flag == 0){
        printf("Ninguém com essas informações encontrado.\n");
    }
    system("pause");
    if(n == 4){
        return cdg;
    }
    else{
        return 0;
    }
}

void erro(){
    int cont;
    system("cls");
                cont = 3;
                printf("Erro ao digitar.\nTente novamente em %d segundo. \n", cont);
                Sleep(1000);
                system("cls");
                cont--;
                printf("Erro ao digitar.\nTente novamente em %d segundo. \n", cont);
                Sleep(1000);
                system("cls");
                cont--;
                printf("Erro ao digitar.\nTente novamente em %d segundo. \n", cont);
                Sleep(1000);
}

void novo_arquivo(int n, unsigned int cdg){
    FILE *a, *b;
    char linha[100];
    Pdados *p;
    p = malloc(sizeof(Pdados));
    unsigned int flag2 = 0;

    // Abre o arquivo de saída uma vez, fora do loop
    if (n == 1) {
        b = fopen("Feminos.txt", "a");
    } else if (n == 2) {
        b = fopen("Masculinos.txt", "a");
    } else if (n == 4) {
        b = fopen("Idade.txt", "a");
    }
    if(b == NULL){
        printf("Erro!\n");
        return;
    }

    a = fopen("ListaUsuarios.txt", "r");
    if(a == NULL){
        printf("Erro!\n");
        fclose(b);
        return;
    }
    else{
        while(fgets(linha, sizeof(linha), a) != NULL){
            sscanf(linha, "%u %[^0-9] %d %c %2d %2d %4d", &p->cdg, p->nome, &p->idade, &p->sexo, &p->Dnasc.dia, &p->Dnasc.mes, &p->Dnasc.ano);
            if(n == 1){
                if(p->sexo == 'F' || p->sexo == 'f'){
                    if(flag2 == 0){
                        fprintf(b, "Mulheres encontradas: \n");
                        flag2++;
                    }
                    fprintf(b, "%d %s %d %c %2d %2d %4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                }
            }
            if(n == 2){
                if(p->sexo == 'M' || p->sexo == 'm'){
                    if(flag2 == 0){
                        fprintf(b, "Homens encontrados: \n");
                        flag2++;
                    }
                    fprintf(b, "%d %s %d %c %2d %2d %4d\n", p->cdg, p->nome, p->idade, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                }
            }
            if(n == 4){
                if(p->idade == cdg){
                    if(flag2 == 0){
                        fprintf(b, "Pessoas de %u anos encontradas: \n", cdg);
                        flag2++;
                    }
                    fprintf(b, "Codigo: %d | Nome --> %s | Sexo --> %c | Nascimento --> %2d/%2d/%4d\n", p->cdg, p->nome, p->sexo, p->Dnasc.dia, p->Dnasc.mes, p->Dnasc.ano);
                }
            }
        }
    }
    free(p);
    fclose(a);
    fclose(b);
}