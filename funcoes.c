#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Função para inicializar a lista de pacientes
void inicializarLista(LISTA* l)
{

}

// Função para criar um novo paciente
PONT criarPaciente(char* nome, int gravidade, time_t horario_chegada)
{

}

// Função para atualizar as posições da lista
void atualizarPosicoes(LISTA* l)
{

}

// Função para inserir um paciente na lista de forma ordenada
void inserirPacienteOrdenado(LISTA* l, PONT novo_paciente)
{

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

}

// Função para salvar a lista de pacientes em um arquivo binário
void salvarPacientesEmArquivo(LISTA* l, char* nome_arquivo)
{

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