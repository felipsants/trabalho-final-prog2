#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 100

int main() {
    // Declaração da lista de todos os pacientes do dia e da lista que será atualizada ao decorrer do dia
    LISTA* listaTotal = (LISTA*)malloc(sizeof(LISTA));
    if (!listaTotal) {
        puts("Erro ao alocar memória pWara listaTotal");
        return 1;
    }
    LISTA* listaAtual = (LISTA*)malloc(sizeof(LISTA));
    if (!listaAtual) {
        puts("Erro ao alocar memória para listaTotal");
        return 1;
    }

    // Inicializar listas
    inicializarLista(listaTotal);
    inicializarLista(listaAtual);

    // Declaração de todas as variáveis que serão utilizadas ao longo da main
    int gravidade;
    time_t horario_chegada;
    int opcao = 0;
    int acesso = 0;
    int quantidade = 0;

    // Fazer os seguintes comandos...
    do {
        char nome[MAX];
        // Funcionalidades disponíveis para o usuário escolher
        printf("\t==========================\n");
        puts("Sistema de Fila para recepcao hospitalar");
        printf("\t==========================\n");
        puts("\t1. Adicionar paciente");
        puts("\t2. Retirar paciente");
        puts("\t3. Pesquisar paciente");
        puts("\t4. Ver lista ordenada");
        puts("\t5. Salvar e sair");
        printf("Escolha uma opcao: ");
        // Ler opção escolhida
        scanf("%d", &opcao);

        switch(opcao) {
            // Adicionar paciente
            case 1:
                // Ler nome do paciente
                printf("\nNome do paciente: ");
                getchar();
                fgets(nome, MAX, stdin);
                // Ler Gravidade dos Sintomas
                printf("\nGravidade dos sintomas (1-10): ");
                scanf("%d", &gravidade);
                // Obter horário de Chegada
                horario_chegada = time(NULL);
                // Criar Paciente 
                PACIENTE* novo_paciente = criarPaciente(nome, gravidade, horario_chegada);
                // Inserir paciente nas listas e ordená-los (Inserction Sort)
                inserirPacienteOrdenado(listaTotal, novo_paciente);
                inserirPacienteOrdenado(listaAtual, novo_paciente);
                break;

            // Retirar paciente atendido da lista atual
            case 2:
                // Ler nome do paciente
                printf("\nNome do paciente ou F para sair: ");
                getchar();
                fgets(nome, MAX, stdin);
                if (strcmp(nome, "F\n") != 0 && strcmp(nome, "f\n") != 0) {
                    // Retirar paciente
                    retirarPaciente(listaAtual, nome);
                    // Atualizar posições da lista
                    atualizarPosicoes(listaAtual);
                }
                else {
                    printf("Saindo... \n");
                    break;
                }
                break;

            // Pesquisar Paciente na lista atual
            case 3:
                // Ler nome do paciente desejado
                printf("\nNome do paciente a pesquisar: ");
                getchar();
                fgets(nome, MAX, stdin);
                // Pesquisar paciente na lista (Busca sequencial)
                PACIENTE* encontrado = pesquisarPaciente(listaAtual, nome);

                // Se o paciente foi encontrado...
                if (encontrado != NULL) {
                    // Printar os dados dele
                    printf("--------------------------------------------\n");
                    printf("Paciente encontrado:\nNome: %sGravidade: %d\nPosicao: %d\nHorario de chegada: %s\n",
                           encontrado->reg.nome, encontrado->reg.gravidade, encontrado->reg.posicao, 
                           ctime(&encontrado->reg.horario_chegada));
                    printf("--------------------------------------------\n");
                } 
                // Se não...
                else {
                    printf("------------------------\n");
                    puts("Paciente nao encontrado.");
                    printf("------------------------\n");
                }
                break;

            // Ver lista ordenada
            case 4:
                // Decidir qual lista deseja acessar
                printf("\nDigite 1 para acessar a lista total ou digite 2 para a lista atual: ");
                scanf("%d", &acesso);

                // Ler a quantidade
                printf("\nQuantidade desejada de pacientes a serem vistos da lista: ");
                scanf("%d", &quantidade);
                
                // Exibir lista total
                if (acesso == 1){
                    exibirLista(listaTotal, quantidade);
                }
                // Exibir lista atual
                else if (acesso == 2){
                    exibirLista(listaAtual, quantidade);
                }
                // Opção inválida
                else{
                    puts("Opção de lista invalida.");
                }
                break;

            // Salvar e sair
            case 5:
                // Obter o horário atual
                time_t now = time(NULL);
                struct tm* t = localtime(&now);

                // Criar uma string para o nome do arquivo com data
                char nome_arquivo_data[150];
                strftime(nome_arquivo_data, sizeof(nome_arquivo_data),
                    "controle_atendimentos_%d-%m-%Y.bin", t);

                // Salvar lista de pacientes em um arquivo binário
                salvarPacientesEmArquivo(listaTotal, nome_arquivo_data);
                // liberar memória alocada para a lista
                liberarLista(listaTotal);
                liberarLista(listaAtual);
                // Mensagem de saída
                printf("Dados salvos. Saindo...\n");
                break;

            // Opção inválida
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 5); // Ficar no loop enquanto opcao for diferente de 5

    return 0;
}