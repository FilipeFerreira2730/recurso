//
// Created by filip on 30/06/2023.
//

#ifndef RECURSO_PED_H
#define RECURSO_PED_H

#endif //RECURSO_PED_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define MAX_PEDIDOS 100

typedef struct date {
    int dd, mm, yy;
    //Dia //Mes //Ano
} DATE;

typedef struct ficheiro {
    DATE date[9];
    char local[30];
} FICHEIRO;

typedef struct frendimento{
    char descricao[50];
    float valor;
} FONTESRENDIMENTO[10];

typedef struct idecisao{
    char resultado[20];// A-aprovado N-nao aprovado
    DATE date[9];
    char justificacao[100];
    char decisor[50];
} INFODECISAO;

typedef struct pedido{
    int numero;
    int identificador;
    char nomeCliente[50];
    char motivoCredito[100];
    DATE date[9];
    char estado[3]; // PA-Por Analisar, EA-Em Análise, A-Analisado
    float montanteTotal;
    int numDecisoes;
    int numFontesRendimento;
    FONTESRENDIMENTO frendimento[20];
    INFODECISAO idecisao[20];
}PEDIDOCREDITO;

typedef struct elem {
    PEDIDOCREDITO pedido;
    struct elem *seguinte;
} ELEM;

typedef struct fila {
    ELEM *primeiro;
    ELEM *ultimo;
} FILA;


int ficheiro_csv(FICHEIRO *f);
int escreverBinario(ELEM *primeiro);
PEDIDOCREDITO novoPedido(FILA* fila);
void enqueue(FILA* fila, PEDIDOCREDITO novoPedido);
int dequeue(FILA* fila, PEDIDOCREDITO* pedidoRemovido);
int front(FILA* fila, PEDIDOCREDITO* pedido);
int isEmpty(FILA* fila);
int size(FILA* fila);
int compareDates(DATE date1[], DATE date2[]);
void ordenarPorDataMaisAntiga(ELEM **primeiro);
void trocar(ELEM** primeiro, ELEM** a, ELEM** b);
int warningAnalisar(ELEM *primeiro);
void analisarPedido(FILA* fila, PEDIDOCREDITO* pedido);
void listarPedidosPorAnalisar(FILA* fila);
void listarPedidosAnalisadosAprovados(FILA* fila);
void escreverRelatorioCreditosAnalisados(FILA* fila);
void ordenarPorValor(ELEM** primeiro);
void listarPedidosAnalisados(FILA* fila);
void listarPedidosPorDecisor(FILA* fila, const char* nomeDecisor);
void gravarPedidosEmArquivo(FILA* fila);
void lerPedidosDeArquivo(FILA* fila);
int inserirPedido(ELEM **primeiro, PEDIDOCREDITO newPedido);
int lerPedidosBinario(ELEM **primeiro);
void imprimeLista(ELEM *inilista);
int sizeLL(ELEM *primeiro);
void alterarDados(ELEM **inilista, int nPedido);
ELEM* anterior(ELEM* primeiro, ELEM* no);
void eliminarPedido(ELEM **primeiro, int nPedido);
int escreverFicheiroTexto(ELEM *primeiro);