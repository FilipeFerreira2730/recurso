//
// Created by filip on 30/06/2023.
//

#ifndef RECURSO_LOGIN_H
#define RECURSO_LOGIN_H

#endif //RECURSO_LOGIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

typedef struct utilizador {
    char nome[100],
    username[100],
    password[100],
    tipo[2]; //1-admin 2-decisor
} UTILIZADOR;

int menuPrincipal();
int menuAdmin();
int menupedcredito();
int menulistagens();
int menuDecisor();
int existeUtilizador(UTILIZADOR u[], char user[], int tam);
int dadosUtilizadorBin(UTILIZADOR u[], int result);
int lerBinUtilizador(UTILIZADOR u[], long res);
void printDadosUtilizador(UTILIZADOR u[], int tam);
void alteraDadosUtilizador(UTILIZADOR u[], int tam);
void removeDadosUtilizador(UTILIZADOR u[], int tam);
void escreverprimeiroregisto();
int loginAdmin(UTILIZADOR u[], int tam);
int loginDecisor(UTILIZADOR u[], int tam);