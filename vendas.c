/*
===========================================================
ARQUIVO: vendas.c

DESCRIÇÃO:
Implementa o módulo de gerenciamento de vendas.

RESPONSABILIDADES:
- Registrar vendas;
- Validar datas;
- Validar clientes e produtos;
- Verificar disponibilidade de estoque;
- Atualizar estoque automaticamente;
- Atualizar total de vendas dos clientes;
- Listar vendas;
- Salvar e carregar vendas em arquivo.
===========================================================
*/

// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#define TAM_VENDAS 10  // Tamanho máximo de vendas

// DEFINICOES DE CORES
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define RESET "\033[0m"

// =================================
// ====== ESTRUTUTRA DE VENDA ======
// =================================
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

// =============================
// ===== VARIÁVEIS GLOBAIS =====
// =============================
Venda vendas[TAM_VENDAS];
int qtdVendas = 0;
int vendasCarregadas = 0;

// ==================================
// ===== PROTOTIPOS DAS FUNCOES =====
// ==================================
void menuVendas();
void incluirVenda();
void listarVendas();

void salvarVendas();
void carregarVendas();

void limparBuffer();
void pausarSistema();

int produtoPossuiVenda(int idProduto);
int validarData(int dia, int mes, int ano);
int anoBissexto(int ano);

int encontrarClientePorCpf(char cpf[]);
int encontrarProdutoPorId(int idProduto);

// ======== FUNCAO DE MENU VENDAS ========
void menuVendas() {

    if(!vendasCarregadas) {
        carregarVendas();
        vendasCarregadas = 1;
    }

    int opcao;

    do {
        system("cls");

        printf("======================================");
        printf("\n=============== VENDAS ===============\n");
        printf("======================================\n");

        printf("\n1 - Incluir venda\n");
        printf("2 - Listar vendas\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                system("cls");
                incluirVenda();
                break;

            case 2:
                system("cls");
                listarVendas();
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf(VERMELHO "\nOpcao invalida! Tente novamente.\n" RESET);
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            pausarSistema();
        }

    } while(opcao != 0);
}
// Final ========================================================

// ================= FUNCAO DE INCLUIR VENDA =================
void incluirVenda() {

    printf("==============================================");
    printf("\n============== INCLUIR VENDA =================\n");
    printf("==============================================\n");

    if(qtdVendas >= TAM_VENDAS) {
        printf(VERMELHO "\nLimite de vendas atingido!\n" RESET);
        return;
    }

    if(qtdClientes == 0) {
        printf(VERMELHO "\nNenhum cliente cadastrado!\n" RESET);
        return;
    }

    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    // Solicita a data da venda
    printf("\nData da venda\n");

    printf("Dia: ");
    scanf("%d", &vendas[qtdVendas].dia);
    limparBuffer();

    printf("Mes: ");
    scanf("%d", &vendas[qtdVendas].mes);
    limparBuffer();

    printf("Ano: ");
    scanf("%d", &vendas[qtdVendas].ano);
    limparBuffer();

    // Valida se a data existe no calendario
    if(!validarData(vendas[qtdVendas].dia, vendas[qtdVendas].mes, vendas[qtdVendas].ano)) {
        printf(VERMELHO "\nData invalida!\n" RESET);
        return;
    }

    // Solicita o CPF do cliente
    printf("\nCPF do cliente: ");
    fgets(vendas[qtdVendas].cpfCliente, 15, stdin);
    vendas[qtdVendas].cpfCliente[
        strcspn(vendas[qtdVendas].cpfCliente, "\n")
    ] = '\0';

    // Procura o cliente pelo CPF
    int posCliente = encontrarClientePorCpf(vendas[qtdVendas].cpfCliente);

    // Se retornar -1, significa que o cliente nao existe
    if(posCliente == -1) {
        printf(VERMELHO "\nCliente nao encontrado!\n" RESET);
        return;
    }

    // Solicita o ID do produto
    printf("ID do produto: ");
    scanf("%d", &vendas[qtdVendas].idProduto);
    limparBuffer();

    // Procura o produto pelo ID
    int posProduto = encontrarProdutoPorId(vendas[qtdVendas].idProduto);

    // Se retornar -1, significa que o produto nao existe
    if(posProduto == -1) {
        printf(VERMELHO "\nProduto nao encontrado!\n" RESET);
        return;
    }

    // Nao permite vender produto deletado
    if(produtos[posProduto].ativo == 0) {
        printf(VERMELHO "\nProduto deletado. Venda nao permitida!\n" RESET);
        return;
    }

    // Solicita a quantidade da venda
    printf("Quantidade vendida: ");
    scanf("%d", &vendas[qtdVendas].quantidade);
    limparBuffer();

    // Nao permite quantidade zero ou negativa
    if(vendas[qtdVendas].quantidade <= 0) {
        printf(VERMELHO "\nQuantidade invalida!\n" RESET);
        return;
    }

    // Verifica se existe estoque suficiente
    if(vendas[qtdVendas].quantidade > produtos[posProduto].quantidade) {
        printf(VERMELHO "\nEstoque insuficiente!\n" RESET);
        printf("Estoque atual: %d\n", produtos[posProduto].quantidade);
        return;
    }

    // Gera o ID unico e sequencial da venda
    vendas[qtdVendas].id = qtdVendas + 1;

    // Baixa automaticamente o estoque do produto vendido
    produtos[posProduto].quantidade -= vendas[qtdVendas].quantidade;

    // Incrementa o total de vendas do cliente
    clientes[posCliente].totalVendas++;

    // Confirma que uma nova venda foi cadastrada no vetor
    qtdVendas++;

    salvarVendas();
    salvarProdutos();
    salvarClientes();

    printf(VERDE "\nVenda cadastrada com sucesso!\n" RESET);
}
// Final ===================================================

// ================== FUNCAO LISTAR VENDAS ==================
void listarVendas() {

    int posCliente;
    int posProduto;

    printf("==============================================");
    printf("\n============== LISTA DE VENDAS ===============\n");
    printf("==============================================\n");

    // Verifica se existe pelo menos uma venda cadastrada
    if(qtdVendas == 0) {
        printf(VERMELHO "\nNenhuma venda cadastrada!\n" RESET);
        return;
    }

    // Cabecalho da tabela
    printf("\n==========================================================================================\n");
    printf("%-4s %-12s %-15s %-18s %-8s %-18s %-5s\n",
        "ID", "Data", "CPF", "Cliente", "Prod.ID", "Produto", "Qtd");
    printf("==========================================================================================\n");
    

    // Percorre todas as vendas cadastradas
    for(int i = 0; i < qtdVendas; i++) {

        // Busca a posicao do cliente pelo CPF salvo na venda
        posCliente = encontrarClientePorCpf(vendas[i].cpfCliente);

        // Busca a posicao do produto pelo ID salvo na venda
        posProduto = encontrarProdutoPorId(vendas[i].idProduto);

        // Mostra os dados da venda em formato de tabela
        printf("%-5d %02d/%02d/%04d   %-15s %-20s %-10d %-20s %-10d\n",
            vendas[i].id,
            vendas[i].dia,
            vendas[i].mes,
            vendas[i].ano,
            vendas[i].cpfCliente,
            clientes[posCliente].nome,
            vendas[i].idProduto,
            produtos[posProduto].nome,
            vendas[i].quantidade);
    }
}
// Final ====================================================


// Funcoes auxiliares/validacao
int produtoPossuiVenda(int idProduto) {
    for(int i = 0; i < qtdVendas; i++) {
        if(vendas[i].idProduto == idProduto) {
            return 1;
        }
    }

    return 0;
}

// Funcao que verifica se um ano e bissexto
int anoBissexto(int ano) {

    if((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        return 1;
    }

    return 0;
}

// Funcao que verifica se uma data e valida
// Retorna:
// 1 -> Data valida
// 0 -> Data invalida
int validarData(int dia, int mes, int ano) {

    // Vetor que armazena a quantidade de dias
    // de cada mes do ano
    //
    // Posicao 0 -> Janeiro   -> 31 dias
    // Posicao 1 -> Fevereiro -> 28 dias
    // Posicao 2 -> Marco     -> 31 dias
    // Posicao 3 -> Abril     -> 30 dias
    // ...
    int diasMes[] = {
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
    };

    // Verifica se o ano e invalido
    // ou se o mes esta fora do intervalo de 1 a 12
    // ou se o dia e menor que 1
    if(ano < 1900 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    }

    // Fevereiro pode ter 29 dias em anos bissextos
    // Exemplo: 2024, 2028, 2032...
    if(mes == 2 && anoBissexto(ano)) {

        // Como fevereiro esta na posicao 1 do vetor,
        // alteramos de 28 para 29 dias
        diasMes[1] = 29;
    }

    // Verifica se o dia informado e maior
    // que a quantidade de dias daquele mes
    //
    // Exemplo:
    // Data: 31/04/2026
    //
    // mes = 4
    // mes - 1 = 3
    // diasMes[3] = 30
    //
    // if(31 > 30)
    // retorna 0 porque abril so possui 30 dias
    if(dia > diasMes[mes - 1]) {
        return 0;
    }

    // Se passou por todas as verificacoes,
    // significa que a data existe
    return 1;
}

void salvarVendas() {
    FILE *arq = fopen("vendas.dat", "wb");

    if(arq != NULL) {
        fwrite(&qtdVendas, sizeof(int), 1, arq);
        fwrite(vendas, sizeof(Venda), qtdVendas, arq);
        fclose(arq);
    }
}

void carregarVendas() {
    FILE *arq = fopen("vendas.dat", "rb");

    if(arq != NULL) {
        fread(&qtdVendas, sizeof(int), 1, arq);
        fread(vendas, sizeof(Venda), qtdVendas, arq);
        fclose(arq);
    }
}