//
// Created by filip on 30/06/2023.
//
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "ped.h"


int ficheiro_csv(FICHEIRO *f) {
    char name[25];
    int res=0;
    int i=0, dadosTemp=0;
    FILE *fpc;
    do {
        printf("Nome do ficheiro\n");
        scanf("%s", name);
    } while((fpc = fopen("name.csv", "r")) == NULL);
    if ((fpc = fopen("name.csv", "r")) == NULL) {
        printf("Ficheiro nao Existe\n");
    } else {
        //res=fscanf(fpc, "%d;%d;%d;%[^;]\n", &f[i].date->dd, &f[i].date->mm, &f[i].date->yy, f[i].local);
        while (res != EOF) {
            res = fscanf(fpc, "%d;%d;%d;%[^;\n]", &f[i].date->dd, &f[i].date->mm, &f[i].date->yy, f[i].local);
            if (res > 0) {
                printf("[%d] - %d/%d/%d, %s\n", i, f[i].date->dd, f[i].date->mm, f[i].date->yy, f[i].local);
                i++;
            }
        }
        printf("Opcao\n");
        scanf("%d", &dadosTemp);
    }
    fclose(fpc);
    return dadosTemp;
}

//LL -> Ficheiro Binario
int escreverBinario(ELEM *primeiro) {
    ELEM *aux = NULL;
    FILE *fp = NULL;

    fp = fopen("ped.dat", "wb");   // Abre o arquivo "ped.dat"

    if (fp == NULL) {
        puts("Erro ao abrir arquivo\n");   // Verifica se abriu corretamente
        return -1;
    }

    for (aux = primeiro; aux != NULL; aux = aux->seguinte) {
        fwrite(&(aux->pedido), sizeof(PEDIDOCREDITO), 1, fp);  // Escreve o conteúdo de cada pedido
    }

    fclose(fp); // Fecha o arquivo
    return 0;
}

//Introduzir um Pedido
PEDIDOCREDITO novoPedido(FILA* fila) {
    PEDIDOCREDITO novoPedido;
    char tipo1[3] = "PA"; // Para Analisar
    char tipo2[3] = "EA"; // Em Análise
    char tipo3[2] = "A";  // Analisado

    printf("Nome do Cliente:\n");
    fflush(stdin);
    gets(novoPedido.nomeCliente);

    printf("Motivo do Crédito:\n");
    fflush(stdin);
    gets(novoPedido.motivoCredito);

    do {
        printf("Estado (PA - Para Analisar / EA - Em Análise / A - Analisado):\n");
        fflush(stdin);
        scanf("%s", novoPedido.estado);
    } while (strcmp(novoPedido.estado, tipo1) != 0 && strcmp(novoPedido.estado, tipo2) != 0 && strcmp(novoPedido.estado, tipo3) != 0);

    printf("Montante Total:\n");
    scanf("%f", &novoPedido.montanteTotal);

    printf("Dia:\n");
    scanf("%d", &novoPedido.date->dd);

    printf("Mês:\n");
    scanf("%d", &novoPedido.date->mm);

    printf("Ano:\n");
    scanf("%d", &novoPedido.date->yy);

    printf("Nome do Decisor:\n");
    fflush(stdin);
    gets(novoPedido.idecisao[0].decisor);

    enqueue(fila, novoPedido);

    return novoPedido;
}

//Queue -> Coloca na queue
void enqueue(FILA* fila, PEDIDOCREDITO novoPedido) {
    ELEM* novoElem = (ELEM*)malloc(sizeof(ELEM));
    novoElem->pedido = novoPedido;
    novoElem->seguinte = NULL;

    if (fila->primeiro == NULL) {
        fila->primeiro = novoElem;
        fila->ultimo = novoElem;
    } else {
        fila->ultimo->seguinte = novoElem;
        fila->ultimo = novoElem;
    }
}

// Queue -> Remove um elemento da fila
int dequeue(FILA* fila, PEDIDOCREDITO* pedidoRemovido) {
    if (fila->primeiro == NULL) {
        // Fila vazia, não há elementos para remover
        return -1;
    }

    ELEM* elementoRemovido = fila->primeiro;
    *pedidoRemovido = elementoRemovido->pedido;

    fila->primeiro = fila->primeiro->seguinte;

    // Se a fila ficar vazia após a remoção, atualiza o ponteiro "ultimo"
    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }

    free(elementoRemovido);

    return 1;
}

// Queue -> Imprime um elemento da fila
int front(FILA* fila, PEDIDOCREDITO* pedido) {
    if (fila->primeiro == NULL) {
        // Fila vazia, não há elementos para imprimir
        return -1;
    }

    *pedido = fila->primeiro->pedido;
    return 1;
}

// Verifica se a fila está vazia
int isEmpty(FILA* fila) {
    if (fila->primeiro == NULL) {
        // Fila vazia
        return 1;
    } else {
        // Fila não vazia
        return 0;
    }
}

// Retorna o tamanho da fila
int size(FILA* fila) {
    int count = 0;
    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        count++;
        atual = atual->seguinte;
    }
    return count;
}

// Comparar datas
int compareDates(DATE date1[], DATE date2[]) {
    if (date1->yy != date2->yy) {
        return date1->yy - date2->yy;
    }
    if (date1->mm != date2->mm) {
        return date1->mm - date2->mm;
    }
    return date1->dd - date2->dd;
}

//Ordenar pedidos pela data mais antiga
void ordenarPorDataMaisAntiga(ELEM **primeiro) {
    ELEM *aux = NULL;
    ELEM *help = NULL;
    ELEM *min = NULL;

    if (*primeiro == NULL) {
        printf("Lista Vazia\n");
        return;
    }

    for (aux = *primeiro; aux != NULL; aux = aux->seguinte) {  // Selection sort
        min = aux;
        for (help = aux; help != NULL; help = help->seguinte) {
            // Comparar as datas - considerando dd, mm, yy
            if (compareDates(min->pedido.date, help->pedido.date) > 0) {
                min = help;
            }
        }
        if (min != aux) {
            trocar(primeiro, &aux, &min);
            aux = min;
        }
    }
}

void trocar(ELEM** primeiro, ELEM** a, ELEM** b) {
    ELEM* temp = *a;
    *a = *b;
    *b = temp;

    // Atualizar os ponteiros dos elementos adjacentes
    if (*a != NULL) {
        (*a)->seguinte = temp->seguinte;
    }
    if (*b != NULL) {
        (*b)->seguinte = temp;
    }
    if (*primeiro == temp) {
        *primeiro = *b;
    }
}

//Avisa quantos Pedidos tem para analisar
int warningAnalisar(ELEM *primeiro) {
    ELEM *aux = NULL;
    int cont = 0;
    char tipo[3] = "PA"; // Para Analisar

    for (aux = primeiro; aux != NULL; aux = aux->seguinte) {
        if (strcmp(aux->pedido.estado, tipo) == 0) {
            cont++;
        }
    }

    return cont;
}

// Função para analisar um pedido de crédito
void analisarPedido(FILA* fila, PEDIDOCREDITO* pedido) {
    // Verificar se o pedido está na fila de análise
    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        if (&atual->pedido == pedido) {
            // Atualizar o estado para "Em Análise"
            strcpy(pedido->estado, "EA");

            // Preencher os campos adicionais
            printf("Informe o resultado da análise (A - Aprovado, N - Não aprovado): ");
            scanf("%s", pedido->idecisao[0].resultado);

            printf("Informe a justificativa da análise: ");
            scanf(" %[^\n]s", pedido->idecisao[0].justificacao);

            printf("Informe o nome do decisor: ");
            scanf(" %[^\n]s", pedido->idecisao[0].decisor);

            // Atualizar a data da análise
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            pedido->idecisao[0].date[0].dd = tm.tm_mday;
            pedido->idecisao[0].date[0].mm = tm.tm_mon + 1;
            pedido->idecisao[0].date[0].yy = tm.tm_year + 1900;

            // Imprimir mensagem de sucesso
            printf("Pedido analisado com sucesso!\n");

            return;
        }
        atual = atual->seguinte;
    }
    // Se chegou aqui, o pedido não foi encontrado na fila
    printf("O pedido não está na fila de análise.\n");
}

void listarPedidosPorAnalisar(FILA* fila) {
    ELEM* atual = fila->primeiro;
    int count = 0;

    printf("Pedidos por analisar:\n");

    while (atual != NULL) {
        if (strcmp(atual->pedido.estado, "PA") == 0) {
            count++;

            // Imprimir informações do pedido
            printf("Pedido %d:\n", count);
            printf("Número: %d\n", atual->pedido.numero);
            printf("Identificador: %d\n", atual->pedido.identificador);
            printf("Nome do Cliente: %s\n", atual->pedido.nomeCliente);
            printf("Motivo do Crédito: %s\n", atual->pedido.motivoCredito);
            printf("Montante Total: %.2f\n", atual->pedido.montanteTotal);
            printf("\n");
        }
        atual = atual->seguinte;
    }

    if (count == 0) {
        printf("Não há pedidos por analisar.\n");
    }
}

// Função para listar os pedidos analisados e aprovados
void listarPedidosAnalisadosAprovados(FILA* fila) {
    ELEM* atual = fila->primeiro;
    int count = 0;

    printf("Pedidos analisados e aprovados:\n");

    while (atual != NULL) {
        if (strcmp(atual->pedido.estado, "A") == 0 && strcmp(atual->pedido.idecisao[0].resultado, "A") == 0) {
            count++;

            // Imprimir informações do pedido
            printf("Pedido %d:\n", count);
            printf("Número: %d\n", atual->pedido.numero);
            printf("Identificador: %d\n", atual->pedido.identificador);
            printf("Nome do Cliente: %s\n", atual->pedido.nomeCliente);
            printf("Motivo do Crédito: %s\n", atual->pedido.motivoCredito);
            printf("Montante Total: %.2f\n", atual->pedido.montanteTotal);
            printf("Data da Análise: %d/%d/%d\n", atual->pedido.idecisao[0].date[0].dd, atual->pedido.idecisao[0].date[0].mm, atual->pedido.idecisao[0].date[0].yy);
            printf("Decisor: %s\n", atual->pedido.idecisao[0].decisor);
            printf("Justificação: %s\n", atual->pedido.idecisao[0].justificacao);
            printf("\n");
        }
        atual = atual->seguinte;
    }

    if (count == 0) {
        printf("Não há pedidos analisados e aprovados.\n");
    }
}

// Função para escrever um relatório em um arquivo de texto com os créditos analisados, ordenados por valor
void escreverRelatorioCreditosAnalisados(FILA* fila) {
    // Ordenar os pedidos por valor (montanteTotal)
    ordenarPorValor(&fila->primeiro);

    // Abrir o arquivo de texto para escrita
    FILE* arquivo = fopen("relatorios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita\n");
        return;
    }

    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->pedido.estado, "A") == 0) {
            // Escrever as informações do pedido no arquivo de texto
            fprintf(arquivo, "Número: %d\n", atual->pedido.numero);
            fprintf(arquivo, "Valor: %.2f\n", atual->pedido.montanteTotal);
            fprintf(arquivo, "Identificador: %d\n", atual->pedido.identificador);
            fprintf(arquivo, "Nome do Cliente: %s\n", atual->pedido.nomeCliente);
            fprintf(arquivo, "Motivo do Crédito: %s\n", atual->pedido.motivoCredito);
            fprintf(arquivo, "Data da Análise: %d/%d/%d\n", atual->pedido.idecisao[0].date[0].dd, atual->pedido.idecisao[0].date[0].mm, atual->pedido.idecisao[0].date[0].yy);
            fprintf(arquivo, "Decisor: %s\n", atual->pedido.idecisao[0].decisor);
            fprintf(arquivo, "Justificação: %s\n", atual->pedido.idecisao[0].justificacao);
            fprintf(arquivo, "\n");
        }
        atual = atual->seguinte;
    }

    // Fechar o arquivo
    fclose(arquivo);
}

// Ordena por ordem crecente
void ordenarPorValor(ELEM** primeiro) {
    int trocou = 1;
    while (trocou) {
        trocou = 0;
        ELEM* atual = *primeiro;
        ELEM* anterior = NULL;

        while (atual != NULL && atual->seguinte != NULL) {
            if (atual->pedido.montanteTotal > atual->seguinte->pedido.montanteTotal) {
                trocar(primeiro, &atual, &(atual->seguinte));
                trocou = 1;
            }
            anterior = atual;
            atual = atual->seguinte;
        }
    }
}

void listarPedidosAnalisados(FILA* fila) {
    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->pedido.estado, "A") == 0) {
            // Imprimir informações do pedido analisado
            printf("Número: %d\n", atual->pedido.numero);
            printf("Identificador: %d\n", atual->pedido.identificador);
            printf("Nome do Cliente: %s\n", atual->pedido.nomeCliente);
            printf("Motivo do Crédito: %s\n", atual->pedido.motivoCredito);
            printf("Data da Análise: %d/%d/%d\n", atual->pedido.idecisao[0].date[0].dd, atual->pedido.idecisao[0].date[0].mm, atual->pedido.idecisao[0].date[0].yy);
            printf("Resultado da Análise: %s\n", atual->pedido.idecisao[0].resultado);
            printf("Justificativa: %s\n", atual->pedido.idecisao[0].justificacao);
            printf("Decisor: %s\n", atual->pedido.idecisao[0].decisor);
            printf("-------------------------------------\n");
        }
        atual = atual->seguinte;
    }
}

void listarPedidosPorDecisor(FILA* fila, const char* nomeDecisor) {
    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        int i;
        for (i = 0; i < 20; i++) {
            if (strcmp(atual->pedido.idecisao[i].decisor, nomeDecisor) == 0 && strcmp(atual->pedido.estado, "A") == 0) {
                // Imprimir informações do pedido
                printf("Número: %d\n", atual->pedido.numero);
                printf("Identificador: %d\n", atual->pedido.identificador);
                printf("Nome do Cliente: %s\n", atual->pedido.nomeCliente);
                printf("Motivo do Crédito: %s\n", atual->pedido.motivoCredito);
                printf("Montante Total: %.2f\n", atual->pedido.montanteTotal);
                printf("-------------------------------------\n");
                break;  // Sai do loop caso encontre uma análise do decisor
            }
        }
        atual = atual->seguinte;
    }
}

void gravarPedidosEmArquivo(FILA* fila) {
    FILE* arquivo = fopen("pedidos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita\n");
        return;
    }

    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "Número: %d\n", atual->pedido.numero);
        fprintf(arquivo, "Identificador: %d\n", atual->pedido.identificador);
        fprintf(arquivo, "Nome do Cliente: %s\n", atual->pedido.nomeCliente);
        fprintf(arquivo, "Motivo do Crédito: %s\n", atual->pedido.motivoCredito);
        fprintf(arquivo, "Montante Total: %.2f\n", atual->pedido.montanteTotal);
        fprintf(arquivo, "Estado: %s\n", atual->pedido.estado);
        fprintf(arquivo, "----------------------\n");

        atual = atual->seguinte;
    }

    fclose(arquivo);
}

void lerPedidosDeArquivo(FILA* fila) {
    FILE* arquivo = fopen("pedidos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para leitura\n");
        return;
    }

    ELEM* atual = fila->primeiro;
    while (atual != NULL) {
        int numero, identificador;
        char nomeCliente[50];
        char motivoCredito[100];
        float montanteTotal;
        char estado[3];

        fscanf(arquivo, "Número: %d\n", &numero);
        fscanf(arquivo, "Identificador: %d\n", &identificador);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", nomeCliente);
        fscanf(arquivo, "Motivo do Crédito: %[^\n]\n", motivoCredito);
        fscanf(arquivo, "Montante Total: %f\n", &montanteTotal);
        fscanf(arquivo, "Estado: %[^\n]\n", estado);
        fscanf(arquivo, "----------------------\n");

        // Atualizar os valores do pedido atual com as informações lidas do arquivo
        atual->pedido.numero = numero;
        atual->pedido.identificador = identificador;
        strcpy(atual->pedido.nomeCliente, nomeCliente);
        strcpy(atual->pedido.motivoCredito, motivoCredito);
        atual->pedido.montanteTotal = montanteTotal;
        strcpy(atual->pedido.estado, estado);

        atual = atual->seguinte;
    }

    fclose(arquivo);
}

//Insere na LL
int inserirPedido(ELEM **primeiro, PEDIDOCREDITO newPedido) {
    ELEM *novo = NULL;
    ELEM *aux = NULL;

    novo = (ELEM*)calloc(1, sizeof(ELEM));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return -1;
    }

    novo->pedido = newPedido;
    novo->seguinte = NULL;

    if (*primeiro == NULL) {
        *primeiro = novo;
    } else {
        aux = *primeiro;
        while (aux->seguinte != NULL) {
            aux = aux->seguinte;
        }
        aux->seguinte = novo;
    }

    return 0;
}

//Binario -> LL
int lerPedidosBinario(ELEM **primeiro) {
    ELEM *aux = NULL;
    FILE *fp = NULL;
    PEDIDOCREDITO temp;
    fp = fopen("ped.dat", "rb");

    if (fp == NULL) {
        return -1;
    }

    while (fread(&temp, sizeof(temp), 1, fp) > 0) {
        inserirPedido(primeiro, temp);
    }

    fclose(fp);
    return 0;
}

//Imprime LL
void imprimeLista(ELEM *inilista) {
    ELEM *aux = NULL;
    int i = 0;

    if (inilista == NULL) {
        printf("Não existem pedidos de crédito!\n");
        return;
    }

    for (aux = inilista; aux != NULL; aux = aux->seguinte) {
        printf("\nNúmero do pedido: %d\n", aux->pedido.numero);
        printf("Identificador: %d\n", aux->pedido.identificador);
        printf("Nome do cliente: %s\n", aux->pedido.nomeCliente);
        printf("Motivo do crédito: %s\n", aux->pedido.motivoCredito);
        printf("Data: %d/%d/%d\n", aux->pedido.date[0].dd, aux->pedido.date[0].mm, aux->pedido.date[0].yy);
        printf("Estado: %s\n", aux->pedido.estado);
        printf("Montante total: %.2f\n", aux->pedido.montanteTotal);

        // Imprimir fontes de rendimento
        for (i = 0; i < aux->pedido.numFontesRendimento; i++) {
            printf("Fonte de rendimento %d: %s\n", i + 1, aux->pedido.frendimento[i]->descricao);
            printf("Valor: %.2f\n", aux->pedido.frendimento[i]->valor);
        }

        // Imprimir informações de decisão
        for (i = 0; i < aux->pedido.numDecisoes; i++) {
            printf("Resultado da decisão %d: %s\n", i + 1, aux->pedido.idecisao[i].resultado);
            printf("Data: %d/%d/%d\n", aux->pedido.idecisao[i].date[0].dd, aux->pedido.idecisao[i].date[0].mm, aux->pedido.idecisao[i].date[0].yy);
            printf("Justificação: %s\n", aux->pedido.idecisao[i].justificacao);
            printf("Decisor: %s\n", aux->pedido.idecisao[i].decisor);
        }
    }
}

//Tamanho da LL
int sizeLL(ELEM *primeiro) {
    ELEM *aux = NULL;
    int count = 0;

    for (aux = primeiro; aux != NULL; aux = aux->seguinte) {
        count++;
    }

    return count;
}

void alterarDados(ELEM **inilista, int nPedido) {
    ELEM *aux = NULL;
    char tipo1[3] = "EA";
    printf("So pode modificar Pedidos do tipo EA - Em Análise\n");

    for (aux = *inilista; aux != NULL; aux = aux->seguinte) {
        if (aux->pedido.numero == nPedido && (strcmp(aux->pedido.estado, tipo1) == 0 || strcmp(aux->pedido.estado, tipo1) == 0)) {
            printf("Indique o novo nome do cliente:\n");
            fflush(stdin);
            gets(aux->pedido.nomeCliente);

            printf("Indique o novo motivo do crédito:\n");
            fflush(stdin);
            gets(aux->pedido.motivoCredito);

            do {
                printf("Indique o novo estado (PA - Para Analisar / EA - Em Análise / A - Analisado):\n");
                fflush(stdin);
                scanf("%s", aux->pedido.estado);
            } while (strcmp(aux->pedido.estado, tipo1) != 0 && strcmp(aux->pedido.estado, tipo1) != 0 && strcmp(aux->pedido.estado, tipo1) != 0);

            printf("Indique o novo montante total:\n");
            scanf("%f", &aux->pedido.montanteTotal);

            printf("Indique o novo dia:\n");
            scanf("%d", &aux->pedido.date[0].dd);

            printf("Indique o novo mês:\n");
            scanf("%d", &aux->pedido.date[0].mm);

            printf("Indique o novo ano:\n");
            scanf("%d", &aux->pedido.date[0].yy);

            printf("Indique o novo nome do decisor:\n");
            fflush(stdin);
            gets(aux->pedido.idecisao[0].decisor);
        }
    }
}

ELEM* anterior(ELEM* primeiro, ELEM* no) {
    if (primeiro == no) {
        return NULL;
    }

    ELEM* aux = NULL;
    ELEM* ant = primeiro;

    for (aux = primeiro->seguinte; aux != NULL; aux = aux->seguinte) {
        if (aux == no) {
            return ant;
        }
        ant = aux;
    }

    return NULL;
}

void eliminarPedido(ELEM **primeiro, int nPedido) {
    ELEM *aux = *primeiro;
    ELEM *anterior = NULL;

    while (aux != NULL && aux->pedido.numero != nPedido) {
        anterior = aux;
        aux = aux->seguinte;
    }

    if (aux == NULL) {
        printf("Não existe tal pedido.\n");
        return;
    }

    if (anterior == NULL) {
        *primeiro = aux->seguinte;
    } else {
        anterior->seguinte = aux->seguinte;
    }

    free(aux);
}

int escreverFicheiroTexto(ELEM *primeiro) {
    ELEM *aux = NULL;
    FILE *fp = NULL;
    int i = 0;
    fp = fopen("pedidos.txt", "w");
    if (fp == NULL) {
        return -1;
    }
    for (aux = primeiro; aux != NULL; aux = aux->seguinte) {
        fprintf(fp, "\n\n---Pedido %i---\nNome do Cliente: %s\nMotivo do Crédito: %s\nEstado: %s\nMontante Total: %.2f\nData: %i/%i/%i\n",
                aux->pedido.numero, aux->pedido.nomeCliente, aux->pedido.motivoCredito, aux->pedido.estado, aux->pedido.montanteTotal,
                aux->pedido.date->dd, aux->pedido.date->mm, aux->pedido.date->yy);
        for (i = 0; i < aux->pedido.numFontesRendimento; i++) {
            fprintf(fp, "Fonte de Rendimento %i: %s - %.2f\n", i + 1, aux->pedido.frendimento[i]->descricao, aux->pedido.frendimento[i]->valor);
        }
        for (i = 0; i < aux->pedido.numDecisoes; i++) {
            fprintf(fp, "Decisão %i:\n", i + 1);
            fprintf(fp, "Resultado: %s\n", aux->pedido.idecisao[i].resultado);
            fprintf(fp, "Data: %i/%i/%i\n", aux->pedido.idecisao[i].date->dd, aux->pedido.idecisao[i].date->mm, aux->pedido.idecisao[i].date->yy);
            fprintf(fp, "Justificação: %s\n", aux->pedido.idecisao[i].justificacao);
            fprintf(fp, "Decisor: %s\n", aux->pedido.idecisao[i].decisor);
        }
    }
    fclose(fp);
    return 0;
}







