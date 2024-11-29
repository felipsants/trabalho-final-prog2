#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Função para inicializar a lista de pacientes
void inicializarLista(LISTA* l){
    l->inicio = NULL;
}

// Função para criar um novo paciente
PONT criarPaciente(char* nome, int gravidade, time_t horario_chegada){
    PACIENTE *novo = (PACIENTE *)malloc(sizeof(PACIENTE));
    if(novo == NULL) {
        printf("Erro ao alocar memória");
        return NULL;
    }
    strcpy(novo->reg.nome, nome);
    novo->reg.gravidade = gravidade;
    novo->reg.horario_chegada = horario_chegada;
    novo->reg.posicao = 0;
    novo->prox = NULL;

    return novo;
}

// Função para atualizar as posições da lista
void atualizarPosicoes(LISTA* l){
    PONT atual = l->inicio;
    int posi = 1;

    while(atual != NULL) {
        atual->reg.posicao = posi;
        posi++;
        atual = atual->prox;
    }
}

// Função para inserir um paciente na lista de forma ordenada
void inserirPacienteOrdenado(LISTA* l, PONT novo_paciente){
    if(l->inicio == NULL || l->inicio->reg.gravidade < novo_paciente->reg.gravidade
        || (l->inicio->reg.gravidade == novo_paciente->reg.gravidade
            && l->inicio->reg.horario_chegada > novo_paciente->reg.horario_chegada))
        {
        novo_paciente->prox = l->inicio;
        l->inicio = novo_paciente;
    }
    else {
        PONT atual = l->inicio;
        while(atual->prox != NULL &&
              (atual->prox->reg.gravidade > novo_paciente->reg.gravidade ||
               (atual->prox->reg.gravidade == novo_paciente->reg.gravidade &&
                atual->prox->reg.horario_chegada <= novo_paciente->reg.horario_chegada))) {
            atual = atual->prox;
        }
        novo_paciente->prox = atual->prox;
        atual->prox = novo_paciente;
    }
    atualizarPosicoes(l);
}

// Função para pesquisar um paciente pelo nome
PONT pesquisarPaciente(LISTA* l, char* nome)
{   
    PONT atual;
    atual = l->inicio;

    while(atual != NULL){
        if(strcmp(atual->reg.nome, nome) == 0){
            return atual;  // Se for igual a 0, ambos as strings sao iguais, logo, paciente encontrado
        }
        atual = atual->prox;
    }

    return NULL;  // Paciente nao encontrado
}

// Função para retirar um paciente da lista com base no nome
void retirarPaciente(LISTA* l, char* nome)
{
    if (l == NULL || l->inicio == NULL) {  // Verifica se a lista esta vazia
        printf("A lista esta vazia.\n");
        return;
    }

    PONT paciente = pesquisarPaciente(l, nome);

    // Verifica se o paciente está na lista
    if(paciente == NULL){
        printf("Paciente nao encontrado.\n");
        return;
    }

    // O paciente desejado está no começo da lista
    if(l->inicio == paciente){

        l->inicio = l->inicio->prox;
        free(paciente);
        printf("Paciente removido com sucesso.\n");

        atualizarPosicoes(l);
        return;
    }


    PONT atual;
    atual = l->inicio;

    // O paciente desejado está em outra posição na lista
    while(atual != NULL){

        if(atual->prox == paciente){

            atual->prox = paciente->prox;
            free(paciente);
            printf("Paciente removido com sucesso.\n");
            atualizarPosicoes(l);
            return;
        }

        atual = atual->prox;
    }

    printf("Paciente nao encontrado.\n");
}

// Função para salvar a lista de pacientes em um arquivo binário
void salvarPacientesEmArquivo(LISTA* l, char* nome_arquivo)
{
    FILE *arq;

    arq = fopen(nome_arquivo,"wb");

    // Verifica se houve erro na criação do arquivo
    if(arq == NULL){
        printf("Erro na abertura do arquivo\n");
        return;
    }

    // Verifica se a lista esta vazia
    if (l == NULL || l->inicio == NULL) {
        fclose(arq);
        printf("A lista esta vazia.\n");
        return;
    }

    PONT atual;
    atual = l->inicio;

    // Percorre a lista, gravando os dados no arquivo
    while(atual != NULL){

        fwrite(&(atual->reg), sizeof(REGISTRO), 1, arq);

        atual = atual->prox;
    }

    // Fechando o arquivo e declarando sucesso
    fclose(arq);
    printf("Pacientes salvos no arquivo '%s'.\n", nome_arquivo);
}

// Função para exibir uma quantidade específica de pacientes ordenados na lista
void exibirLista(LISTA* l, int quantidade)
{
    if (l == NULL || l->inicio == NULL) {  // Verifica se a lista esta vazia
        printf("A lista esta vazia ou a quantidade solicitada eh invalida.\n");
        return;
    }

    if (quantidade <= 0) {  // Garante que "quantidade" seja positivo e maior que 0
        printf("Quantidade solicitada eh invalida.\n");
        return;
    }

    PONT atual;
    atual = l->inicio;
    int count = 0;  

    while((atual != NULL) && (count < quantidade)){
        printf("Posicao: %d \n", atual->reg.posicao);
        printf("Nome: %s \n", atual->reg.nome);
        printf("Gravidade: %d \n", atual->reg.gravidade);
        printf("Horario de Chegada: %s", ctime(&atual->reg.horario_chegada));
        printf("------------------------\n");  // Facilita visualmente a separacao entre pacientes
        atual = atual->prox;
        count++;
    }
}

// Função para liberar a memória alocada para a lista de pacientes
void liberarLista(LISTA* l)
{
    if(l == NULL)  // Verifica se a lista esta vazia
        return;

    PONT atual;
    atual = l->inicio;

    while(atual != NULL){
        PONT apagar = atual;
        atual = atual->prox;
        free(apagar);
    }

    l->inicio = NULL;
}