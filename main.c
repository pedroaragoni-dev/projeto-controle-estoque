#include <stdio.h>
#include <stdlib.h>
#include "produtos.c"
#include "clientes.c"
#include "vendas.c"

#define TAM_VENDAS 10  // Tamanho máximo de vendas

// DEFINICOES DE CORES
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define RESET "\033[0m"

/*========== ESTRUTURA DE VENDA ==========*/
typedef struct {
    int id; // ID único da venda

    // Conjunto de variáveis que formam data
    // Foi decomposto em partes para facilitar na validação
    int dia;
    int mes;
    int ano;

    char cpfCliente[15]; // Cpf do cliente associado a venda

    int idProduto; // ID do produto vendido
    int quantidade; // Quantidade de vendida

} Venda;

// Assinaturas das funções
void menuProdutos(); // Assinatura da funcao que mostra o menu de produtos
void menuClientes(); // Assinatura da funcao que mostra o menu de clientes
void menuVendas(); // Assinatura da funcao que mostra o menu de vendas

void limparBuffer() {
    while (getchar() != '\n');
}

void pausarSistema() {
    printf(AMARELO "\nPressione enter para continuar...\n" RESET);
    getchar();
}

int main() {

    system("cls"); // Limpar a tela no início( futuramente uma função )

    
    Venda vendas[TAM_VENDAS];

    int opcao;

    do {
        system("cls");

        printf("==============================================");
        printf("\n======= SISTEMA DE CONTROLE DE ESTOQUE =======\n");
        printf("==============================================\n");

        // Menu principal
        printf("\n1 - Produtos\n");
        printf("2 - Clientes\n");
        printf("3 - Vendas\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {

            case 1:
                system("cls");
                menuProdutos();
                break;
            
            case 2:
                system("cls");
                menuClientes();
                break;

            case 3: 
                system("cls");
                menuVendas();
                break;

            case 0:
                system("cls");
                printf("\nEncerrando o programa...\n");
                break;

            default:
                system("cls");
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            pausarSistema();
        }
    } while(opcao != 0);

    return 0;

}