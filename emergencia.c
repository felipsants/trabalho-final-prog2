#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 100

int main() {
    // Declaração da lista de todos os pacientes do dia e da lista que será atualizada ao decorrer do dia
    PACIENTE* listaTotal, *listaAtual;
    // Inicializar listas
    inicializarLista(listaTotal);
    inicializarLista(listaAtual);
    // Declaração de todas as variáveis que serão utilizadas ao longo da main
    char nome[MAX];
    int gravidade;
    time_t horario_chegada;
    int opcao;
    int acesso;
    int quantidade;
    char nome_arquivo[] = "controle_atendimentos.bin";

    // Fazer os seguintes comandos...
    do {
        // Funcionalidades disponíveis para o usuário escolher
        puts("1. Adicionar paciente");
        puts("2. Retirar paciente");
        puts("3. Pesquisar paciente");
        puts("4. Ver lista ordenada");
        puts("5. Salvar e sair");
        printf("Escolha uma opcao: ");
        // Ler opção escolhida
        scanf("%d", &opcao);

        switch(opcao) {
            // Adicionar paciente
            case 1:
                // Ler nome do paciente
                printf("Nome do paciente: ");
                fgets(nome, MAX, stdin);
                // Ler Gravidade dos Sintomas
                printf("Gravidade dos sintomas (1-10): ");
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
                // Retirar paciente
                retirarPaciente(listaAtual, nome);
                // Atualizar posições da lista
                atualizarPosicoes(listaAtual);

            // Pesquisar Paciente na lista atual
            case 3:
                // Ler nome do paciente desejado
                printf("Nome do paciente a pesquisar: ");
                scanf("%s", nome);
                // Pesquisar paciente na lista (Busca sequencial)
                PACIENTE* encontrado = pesquisarPaciente(listaAtual, nome);
                // Se o paciente foi encontrado...
                if (encontrado != NULL) {
                    // Printar os dados dele
                    printf("Paciente encontrado: %s, Gravidade: %d, Horario de chegada: %s\n", 
                           encontrado->reg.nome, encontrado->reg.gravidade, ctime(&encontrado->reg.horario_chegada));
                } 
                // Se não...
                else {
                    puts("Paciente nao encontrado.");
                }
                break;

            // Ver lista ordenada
            case 4:
                // Decidir qual lista deseja acessar
                printf("Digite 1 para acessar a lista total ou digite 2 para a lista atual: ");
                scanf("%d", acesso);

                // Ler a quantidade
                printf("Quantidade desejada de pacientes a serem vistos da lista: ");
                scanf("%d", quantidade);
                
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
                // Salvar lista de pacientes em um arquivo binário
                salvarPacientesEmArquivo(listaTotal, nome_arquivo);
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