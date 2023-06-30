//
// Created by filip on 30/06/2023.
//

#include <stdio.h>
#include "login.h"

int menuPrincipal() {
    int opP=0;
    do {
        printf("\n\t**** Menu de Principal ****\n");
        printf("\t**  [1] Administrador      **\n");
        printf("\t**  [2] Decisor            **\n");
        printf("\t**  [0] Sair               **\n");
        printf("\t*****************************\n");
        printf("\nQual é a sua função?");
        scanf("%i", &opP);
    } while(opP<0||opP>2);
    return opP;
}

int menuAdmin() {
    int opA=0;
    do {
        printf("\n\t****** Menu de Administrador ******\n");
        printf("\t**   [1] Registar utilizador       **\n");
        printf("\t**   [2] Alterar utilizador        **\n");
        printf("\t**   [3] Remover utilizador        **\n");
        printf("\t**   [4] Listar utilizadores       **\n");
        printf("\t**   [5] Gerir pedidos de credito  **\n");
        printf("\t**   [6] Listagens                 **\n");
        printf("\t**   [0] Menu de Entrada           **\n");
        printf("\t*******************************\n");
        printf("\nIntroduza a sua opcao:");
        scanf("%i", &opA);
    } while(opA<0||opA>6);
    return opA;
}

int menupedcredito() {
    int opPC=0;
    do {
        printf("\n\t*************** Gerir pedidos de credito ***************\n");
        printf("\t**    [1] Criar pedido de credito                       **\n");
        printf("\t**    [2] Listar pedidos de credito                     **\n");
        printf("\t**    [3] Alterar pedido de credito                     **\n");
        printf("\t**    [4] Eliminar pedidos de credito                   **\n");
        printf("\t**    [0] Menu de Administrador                         **\n");
        printf("\t**********************************************************\n");
        printf("\nIntroduza a sua opcao:\n");
        scanf("%i", &opPC);
    } while(opPC<0||opPC>4);
    return opPC;
}

int menulistagens() {
    int opL=0;
    do {
        printf("\n\t********************************** Listagens **********************************\n");
        printf("\t**    [1] Listar os pedidos de crédito por analisar                            **\n");
        printf("\t**    [2] Listar os pedidos de crédito analisados                              **\n");
        printf("\t**    [3] Listar os pedidos de crédito analisados/aprovados                    **\n");
        printf("\t**    [4] Listar os pedidos de crédito com um montante acima de um dado valor  **\n");
        printf("\t**    [5] Listar os pedidos de crédito  analisados por um “decisor”            **\n");
        printf("\t**    [6] Relatorio com dados analisados por valor                             **\n");
        printf("\t**    [0] Menu de Administrador                                                **\n");
        printf("\t*********************************************************************************\n");
        printf("\nIntroduza a sua opcao:\n");
        scanf("%i", &opL);
    } while(opL<0||opL>6);
    return opL;
}

int menuDecisor() {
    int opD=0;
    do {
        printf("\n\t*********** Menu de decisor ***********\n");
        printf("\t**  [1] Analisar pedidos de credito    **\n");
        printf("\t**  [0] Menu de Entrada                **\n");
        printf("\t*****************************************\n");
        printf("\nIntroduza a sua opcao:");
        scanf("%i", &opD);
    } while(opD<0||opD>1);
    return opD;
}

int existeUtilizador(UTILIZADOR u[], char user[], int tam) {
    int i=0;
    for(i=0;i<tam;i++) {
        if(strcmp(user, u[i].username)==0) {
            return 1;
        }
    }
    return 0;
}

int dadosUtilizadorBin(UTILIZADOR u[], int result) {
    UTILIZADOR *ut=NULL;
    char tipo1[2]="A", tipo2[2]="D";
    char passTemp[100]; //Password temporária
    FILE *fplogin=NULL;
    ut = (UTILIZADOR *)calloc(1, sizeof(UTILIZADOR));
    if (ut == NULL) {
        printf("Out of memory!\n");
    }
    fplogin = fopen("login.dat", "ab");
    if (fplogin == NULL) {
        printf("Erro na ABERTURA do ficheiro!\n");
    }

    printf("\nIntroduza o nome do utilizador: ");
    fflush(stdin);
    gets(ut->nome);
    do {
        printf("\nIntroduza o username do utilizador: ");
        fflush(stdin);
        gets(ut->username);
        fflush(stdin);
        if (existeUtilizador(u, ut->username, result)==1) {
            printf("Esse username já existe!\n");
        }
    } while(existeUtilizador(u, ut->username, result)==1);
    do {
        printf("\nIntroduza a password do utilizador: ");
        fflush(stdin);
        gets(ut->password);
        printf("\nIntroduza novamente a password do utilizador: ");
        fflush(stdin);
        gets(passTemp);
    } while (strcmp(ut->password, passTemp)!=0);
    do {
        printf("\nIntroduza o tipo de utilizador (A-Administrador / D-Decisor): ");
        fflush(stdin);
        scanf("%s", &ut->tipo);
    } while(strcmp(ut->tipo, tipo1)!=0 && strcmp(ut->tipo, tipo2)!=0);
    fwrite(&ut[0],sizeof(UTILIZADOR),1,fplogin);
    free(ut);
    fclose(fplogin);
}

int lerBinUtilizador(UTILIZADOR u[], long res) {
    FILE *fplogin=NULL;
    int i=0;
    fplogin = fopen("login.dat", "rb");
    if (fplogin == NULL) {
        printf("Erro na abertura do ficheiro\n");
    }
    res=fread(u, sizeof(UTILIZADOR), sizeof(fplogin), fplogin);
    fread(u, sizeof(UTILIZADOR), res, fplogin);
    fclose(fplogin);
    return res;
}

void printDadosUtilizador(UTILIZADOR u[], int tam) {
    int i=0;
    for(i=0;i<tam;i++) {
        printf("\nNome: %s\n", &u[i].nome);
        printf("Username de %s: %s\n", &u[i].nome, &u[i].username);
        printf("Password de %s: %s\n", &u[i].nome, &u[i].password);
        printf("Tipo de %s: %s\n", &u[i].nome, &u[i].tipo);
    }
}

void alteraDadosUtilizador(UTILIZADOR u[], int tam) {
    char usernameProc[100];
    char nomeTemp[100], userTemp[100], passTemp[100], tipoTemp[2];
    int i=0;
    FILE *fplogin=NULL;
    fplogin = fopen("login.dat", "rb");
    if (fplogin == NULL) {
        printf("Erro na abertura do ficheiro 1\n");
    }
    FILE *fplogin1=NULL;
    fplogin1 = fopen("login1.dat", "wb");
    if (fplogin1 == NULL) {
        printf("Erro na abertura do ficheiro Temp\n");
    }
    printf("Introduza o username do utilizador que pretende procurar\n");
    fflush(stdin);
    gets(usernameProc);
    for(i=0; i<tam; i++) {
        if (strcmp(usernameProc, u[i].username)==0) {
            printf("\nNome: %s\n", &u[i].nome);
            printf("Username de %s: %s\n", &u[i].nome, &u[i].username);
            printf("Password de %s: %s\n", &u[i].nome, &u[i].password);
            printf("Tipo de %s: %s\n", &u[i].nome, &u[i].tipo);
            printf("\nIntroduza o novo nome:\n");
            fflush(stdin);
            gets(u[i].nome);
            printf("\nIntroduza o novo username:\n");
            fflush(stdin);
            gets(u[i].username);
            printf("\nIntroduza a nova password:\n");
            fflush(stdin);
            gets(u[i].password);
            printf("\nIntroduza o novo tipo de utilizador:\n");
            fflush(stdin);
            gets(u[i].tipo);
        }
    }
    fwrite(&u[0], sizeof(UTILIZADOR), tam, fplogin1);
    fclose(fplogin1);
    fclose(fplogin);
    remove("login.dat");
    rename("login1.dat","login.dat");
    fclose(fplogin1);
    fclose(fplogin);
}

void removeDadosUtilizador(UTILIZADOR u[], int tam) {
    char usernameProc[100];
    int i=0, j=0;
    FILE *fplogin=NULL;
    fplogin = fopen("login.dat", "rb");
    if (fplogin == NULL) {
        printf("Erro na abertura do ficheiro 1\n");
    }
    FILE *fplogin1=NULL;
    fplogin1 = fopen("login1.dat", "wb");
    if (fplogin1 == NULL) {
        printf("Erro na abertura do ficheiro Temp\n");
    }
    printf("Introduza o username do utilizador que pretende ELIMINAR\n");
    fflush(stdin);
    gets(usernameProc);
    for(i=0; i<tam; i++) {
        if (strcmp(usernameProc, u[i].username) == 0) {
            printf("\nNome: %s\n", u[i].nome);
            printf("Username de %s: %s\n", u[i].nome, u[i].username);
            printf("Password de %s: %s\n", u[i].nome, u[i].password);
            printf("Tipo de utilizador: %s\n", u[i].tipo);
            for(j=i;j<tam-1;j++) {
                u[j] = u[j+1];
            }
            tam--;
        }
    }
    fwrite(&u[0], sizeof(UTILIZADOR), tam, fplogin1);
    fclose(fplogin1);
    fclose(fplogin);
    remove("login.dat");
    rename("login1.dat","login.dat");
    fclose(fplogin1);
    fclose(fplogin);
}

void escreverprimeiroregisto() {
    UTILIZADOR firstU[1]={"admin", "admin", "12345", "A"};
    FILE *fplogin=NULL;
    fplogin = fopen("login.dat", "wb");
    if (fplogin == NULL) {
        printf("Erro na abertura do ficheiro\n");
    }
    fwrite(&firstU[0], sizeof(UTILIZADOR), 1, fplogin);
    fclose(fplogin);
}


int loginAdmin(UTILIZADOR u[], int tam) {
    int i=0;
    char tipo1[2]="A";
    char userTemp[100], passTemp[100];
    printf("\nIntroduza aqui o seu username: ");
    fflush(stdin);
    gets(userTemp);
    printf("\nIntroduza aqui a sua password: ");
    fflush(stdin);
    gets(passTemp);
    for(i=0; i<tam; i++) {
        if (strcmp(userTemp, u[i].username) == 0 && strcmp(passTemp, u[i].password) == 0) {
            if (strcmp(u[i].tipo, tipo1) == 0) {
                printf("Bem-vindo Administrador %s\n", u[i].nome);
                return 1;
            }
        }
    }
    return 0;
}

int loginDecisor(UTILIZADOR u[], int tam) {
    int i=0;
    char tipo1[2]="D";
    char userTemp[100], passTemp[100];
    printf("\nIntroduza aqui o seu username: ");
    fflush(stdin);
    gets(userTemp);
    printf("\nIntroduza aqui a sua password: ");
    fflush(stdin);
    gets(passTemp);
    for(i=0; i<tam; i++) {
        if (strcmp(userTemp, u[i].username) == 0 && strcmp(passTemp, u[i].password) == 0) {
            if (strcmp(u[i].tipo, tipo1) == 0) {
                printf("Bem-vindo Decisor %s\n", u[i].nome);
                return i;
            }
        }
    }
    return 0;
}