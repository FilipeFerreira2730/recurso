#include <stdio.h>
#include "login.h"

int main(int argc, char **argv) {
    //-------------------------------------------//
    setlocale(LC_ALL, "Portuguese");
    //-------------------------------------------//
    UTILIZADOR *u;
    FILE *fplogin=NULL;
    int opP=0, opA=0, opPC=0, opL=0, opD=0;
    int nAta=0;
    long result=0, res=0;
    int tam=0, qtd=0;
    char name[100];
    int j=0;
    int cont=0;
    int contador=0;
    //------------------------------------------//
    if((fplogin = fopen("login.dat", "rb")) == NULL) {
        escreverprimeiroregisto(); //admin 12345
    }
    result=lerBinUtilizador(u, res);
    do {
        opP=menuPrincipal();
        switch(opP) {
            //----------------------------------//
            //		Opcoes do ADMINISTRADOR		//
            case 1: {
                if(loginAdmin(u, result)==1){
                    do {
                        opA=menuAdmin();
                        switch(opA) {
                            case 1: { //Registar utilizador
                                printf("Criar conta de utilizador\n");
                                dadosUtilizadorBin(u, result);
                                result=lerBinUtilizador(u, res);
                                break;
                            }
                            case 2: { //Alterar dados do utilizador
                                alteraDadosUtilizador(u, result);
                                result=lerBinUtilizador(u, res);
                                break;
                            }
                            case 3:{ //Remover conta do utilizador
                                removeDadosUtilizador(u, result);
                                result=lerBinUtilizador(u, res);
                                break;
                            }
                            case 4: { //Listar contas de utilizador
                                printDadosUtilizador(u, result);
                                break;
                            }
                            case 5: { //Gerir pedidos de credito
                                do {
                                    opGA=menupedcredito();
                                    switch(opGA) {
                                        case 1: { // Criar pedido de credito
                                            break;
                                        }
                                        case 2: { //Listar pedidos de credito
                                            break;
                                        }
                                        case 3: { //Alterar pedido de credito
                                            break;
                                        }
                                        case 4: { //Eliminar pedidos de credito
                                            break;
                                        }
                                    }
                                } while(opGA!=0);
                            }
                            case 6: { //Menu das listagens
                                do {
                                    opGA=menulistagens();
                                    switch(opGA) {
                                        case 1: { //Listar os pedidos de crédito por analisar
                                            break;
                                        }
                                        case 2: { //Listar os pedidos de crédito analisados
                                            break;
                                        }
                                        case 3: { //Listar os pedidos de crédito analisados/aprovados
                                            break;
                                        }
                                        case 4: { //Listar os pedidos de crédito com um montante acima de um dado valor
                                            break;
                                        }
                                        case 5: { //Listar os pedidos de crédito  analisados por um “decisor”
                                            break;
                                        }
                                        case 6: { //Relatorio com dados analisados por valor
                                            break;
                                        }
                                    }
                                } while(opGA!=0);
                            }
                        }
                    }	while(opA!=0);
                }
                else {
                    printf("Dados incorretos ou utilizador sem permissoes para este cargo!\n");
                }
                break;
            }
            case 2: {   //Login Decisor
                /*else {
                    printf("Dados incorretos ou utilizador sem permissões para este cargo!\n");
                }
                break;*/
            }
        }
    }
    while(opP!=0);
    return 0;
}
