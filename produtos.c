// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// DEFINICOES DE TAMANHOS
#define TAM_PRODUTOS 10 // Tamanho máximo de produtos
#define TAM_NOME_PRODUTO 50 // Tamanho maximo de caracteres no nome do produto

// DEFINICOES DE CORES
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define RESET "\033[0m"

// =================================
// ===== ESTRUTUTRA DO PRODUTO =====
// =================================
typedef struct {
    int id; //ID único do produto
    char nome[TAM_NOME_PRODUTO]; // Nome do produto
    int quantidade; // Quantidade em estoque
    float preco; // Preco unitário do produto
    int ativo; // 1=ativo / 0=deletado
} Produto;

// =============================
// ===== VARIÁVEIS GLOBAIS =====
// =============================
Produto produtos[TAM_PRODUTOS];
int qtdProdutos = 0;

// ==================================
// ===== PROTOTIPOS DAS FUNCOES =====
// ==================================
void menuProdutos();
void incluirProdutos();

void limparBuffer();
void pausarSistema();

int nomeDuplicado(char nome[]);


void menuProdutos() {
    int opcao;

    do {
        system("cls");

        printf("======================================");
        printf("\n============== PRODUTOS ==============\n");
        printf("======================================\n");

        printf("\n1 - Incluir produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto\n");
        printf("4 - Atualizar estoque\n");
        printf("5 - Valor total\n");
        printf("6 - Estoque baixo\n");
        printf("7 - Excluir produto\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {

            case 1:
                system("cls");
                incluirProdutos();
                break;

            case 2:
                system("cls");
                printf("\nListar produtos\n");
                break;
                
            case 3:
                system("cls");
                printf("\nBuscar produto\n");
                break;
            case 4:
                system("cls");
                printf("\nAtualizar estoque\n");
                break;
            case 5:
                system("cls");
                printf("\nCalcular valor total do estoque\n");
                break;
            case 6:
                system("cls");
                printf("\nRelatorio de estoque baixo\n");
                break;
            case 7:
                system("cls");
                printf("\nExcluir produto\n");
                break;
            case 0:
                system("cls");
                printf("\nVoltando...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            pausarSistema();
        }

    } while(opcao != 0);
}

int nomeDuplicado(char nome[]) {
    for(int i=0; i< qtdProdutos; i++) {
        if(produtos[i].ativo == 1 && strcasecmp(produtos[i].nome, nome) == 0) {
            return 1;
        }
    }

    return 0;
}

void incluirProdutos() {

    printf("==============================================");
    printf("\n============ CADASTRO DE PRODUTO =============\n");
    printf("==============================================\n");

    // Verifica se a qtd de produtos é maior que o limite definido no vetor
    // Se for maior, sai da funcao de incluir e volta pro menu
    if(qtdProdutos >= TAM_PRODUTOS) {
        printf("\nLimite de produtos alcancado!");
        printf("\nProdutos cadastrados: %d", qtdProdutos);
        return;
    }

    printf("\nNome: ");
    fgets(produtos[qtdProdutos].nome, TAM_NOME_PRODUTO, stdin);
    produtos[qtdProdutos].nome[strcspn(produtos[qtdProdutos].nome, "\n")] = '\0';
    
    if(strlen(produtos[qtdProdutos].nome) == 0) {
        printf(VERMELHO "\nNome invalido\n" RESET);
        return;
    }

    if(nomeDuplicado(produtos[qtdProdutos].nome)) {
        printf(VERMELHO "\nProduto ja cadastrado\n" RESET);
        return;
    }
    
    printf("Quantidade inicial em estoque: ");
    scanf("%d", &produtos[qtdProdutos].quantidade);
    limparBuffer();

    if(produtos[qtdProdutos].quantidade < 0) {
        printf(VERMELHO "\nQuantidade invalida\n" RESET);
        return;
    }

    printf("Preco unitario: R$ ");
    scanf("%f", &produtos[qtdProdutos].preco);
    limparBuffer();

    if(produtos[qtdProdutos].preco <= 0) {
        printf(VERMELHO "\nPreco Invalido\n" RESET);
        return;
    }

    produtos[qtdProdutos].id = qtdProdutos + 1; 
    produtos[qtdProdutos].ativo = 1;

    qtdProdutos++;

    printf(VERDE "\nProduto cadastrado com sucesso!\n" RESET);
    
}



