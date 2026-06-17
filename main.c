#include <stdio.h>
#include <stdlib.h>
#include "produtos.c"
#include "clientes.c"
#include "vendas.c"

#define TAM_PRODUTOS 10 // Tamanho máximo de produtos
#define TAM_CLIENTES 10 // Tamanho máximo de clientes
#define TAM_VENDAS 10  // Tamanho máximo de vendas

/*========== ESTRUTURA DO PRODUTO ==========*/ 
typedef struct {
    int id; //ID único do produto
    char nome[50]; // Nome do produto
    int quantidade; // Quantidade em estoque
    float preco; // Preco unitário do produto
    int ativo; // 1=ativo / 0=deletado

} Produto;

/*========== ESTRUTURA DE CLIENTE ==========*/
typedef struct {
    char nome[50]; // Nome do cliente
    char cpf[15]; // CPF do cliente
    int totalVendas; // Quantidade de vendas realizadas

} Cliente;

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

int main() {

    system("cls"); // Limpar a tela no início( futuramente uma função )

    Produto produtos[TAM_PRODUTOS];
    Cliente clientes[TAM_CLIENTES];
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
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }
    } while(opcao != 0);

    return 0;

}