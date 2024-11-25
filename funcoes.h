#ifndef FUNCOES_H
#define FUNCOES_H

#include <time.h>

// Estrutura para armazenar informações de um paciente
typedef struct {
    char nome[100]; // Nome do paciente
    int gravidade; // Nível de gravidade dos sintomas
    time_t horario_chegada; // Horário de chegada
    int posicao; // Posição atual na lista
} REGISTRO;

// Estrutura do nó da lista ligada
typedef struct aux {
    REGISTRO reg;
    struct aux* prox; // Ponteiro para o próximo paciente da lista
} PACIENTE;

typedef PACIENTE* PONT;

// Estrutura para a lista de pacientes
typedef struct {
    PONT inicio;
} LISTA;

// Função para inicializar a lista de pacientes
void inicializarLista(LISTA* l);

// Função para criar um novo paciente
PONT criarPaciente(char* nome, int gravidade, time_t horario_chegada);

// Função para atualizar as posições da lista
void atualizarPosicoes(LISTA* l);

// Função para inserir um paciente na lista de forma ordenada
void inserirPacienteOrdenado(LISTA* l, PONT novo_paciente);

// Função para pesquisar um paciente pelo nome
PONT pesquisarPaciente(LISTA* l, char* nome);

// Função para retirar um paciente da lista com base no nome
void retirarPaciente(LISTA* l, char* nome);

// Função para salvar a lista de pacientes em um arquivo binário
void salvarPacientesEmArquivo(LISTA* l, char* nome_arquivo);

// Função para exibir uma quantidade específica de pacientes ordenados na lista
void exibirLista(LISTA* l, int quantidade);

// Função para liberar a memória alocada para a lista de pacientes
void liberarLista(LISTA* l);

#endif // FUNCOES_H