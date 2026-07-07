/*
===========================================================
ARQUIVO: clientes.c

DESCRIÇÃO:
Implementa o módulo de gerenciamento de clientes.

RESPONSABILIDADES:
- Cadastrar clientes;
- Validar CPF;
- Verificar CPF duplicado;
- Listar clientes;
- Controlar o total de vendas;
- Salvar e carregar clientes em arquivo.
===========================================================
*/

// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINICOES DE TAMANHOS
#define TAM_CLIENTES 10

// DEFINICOES DE CORES
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define RESET "\033[0m"

// ================================
// ===== ESTRUTURA DE CLIENTE =====
// ================================
typedef struct {
    char nome[50];      // Nome do cliente
    char cpf[15];       // CPF do cliente
    int totalVendas;    // Quantidade de vendas realizadas
} Cliente;

// =============================
// ===== VARIÁVEIS GLOBAIS =====
// =============================
Cliente clientes[TAM_CLIENTES];
int qtdClientes = 0;
int clientesCarregados = 0;

// ==================================
// ===== PROTOTIPOS DAS FUNCOES =====
// ==================================
void menuClientes();
void incluirCliente();
void listarClientes();

void salvarClientes();
void carregarClientes();

void limparBuffer();
void pausarSistema();

int validarCPF(char cpf[]);
int cpfDuplicado(char cpf[]);
int encontrarClientePorCpf(char cpf[]);

// ==================== FUNCAO DE MENU DE CLIENTES ====================
void menuClientes() {

    if(!clientesCarregados) {
        carregarClientes();
        clientesCarregados = 1;
    }

    int opcao;

    do {

        system("cls");

        printf("======================================\n");
        printf("============== CLIENTES ==============\n");
        printf("======================================\n");

        printf("\n1 - Incluir cliente");
        printf("\n2 - Listar clientes");
        printf("\n0 - Voltar");

        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {

            case 1:
                system("cls");
                incluirCliente();
                break;

            case 2:
                system("cls");
                listarClientes();
                break;

            case 0:
                system("cls");
                printf(VERDE "\nVoltando...\n" RESET);
                break;

            default:
                printf(VERMELHO "\nOpcao invalida!\n" RESET);
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            pausarSistema();
        }

    } while(opcao != 0);
}
// Final ================================================================

// ===================== FUNCAO DE INCLUIR CLIENTES =====================
void incluirCliente() {

    if(qtdClientes >= TAM_CLIENTES) {
        printf(VERMELHO "\nLimite de clientes atingido!\n" RESET);
        return;
    }

    printf("\nNome completo: ");
    fgets(clientes[qtdClientes].nome, 50, stdin);
    clientes[qtdClientes].nome[
        strcspn(clientes[qtdClientes].nome, "\n")
    ] = '\0';

    // Nome não pode ser vazio
    if(strlen(clientes[qtdClientes].nome) == 0) {
        printf(VERMELHO "\nNome invalido!\n" RESET);
        return;
    }

    printf("CPF (somente numeros): ");
    fgets(clientes[qtdClientes].cpf, 15, stdin);
    clientes[qtdClientes].cpf[
        strcspn(clientes[qtdClientes].cpf, "\n")
    ] = '\0';

    // Validação oficial do CPF
    if(!validarCPF(clientes[qtdClientes].cpf)) {
        printf(VERMELHO "\nCPF invalido!\n" RESET);
        return;
    }

    // Verifica CPF duplicado
    if(cpfDuplicado(clientes[qtdClientes].cpf)) {
        printf(VERMELHO "\nCPF ja cadastrado!\n" RESET);
        return;
    }

    // Inicializa total de vendas
    clientes[qtdClientes].totalVendas = 0;

    qtdClientes++;

    salvarClientes();

    printf(VERDE "\nCliente cadastrado com sucesso!\n" RESET);
}
// Final ===================================================================

// ======================= FUNCAO DE LISTAR CLIENTES =======================
void listarClientes() {

    if(qtdClientes == 0) {
        printf(VERMELHO "\nNenhum cliente cadastrado!\n" RESET);
        return;
    }

    printf("\n=========================================================\n");
    printf("%-15s %-25s %-10s\n",
        "CPF", "Nome", "Vendas");
    printf("=========================================================\n");

    for(int i = 0; i < qtdClientes; i++) {

        printf("%-15s %-25s %-10d\n",
            clientes[i].cpf,
            clientes[i].nome,
            clientes[i].totalVendas);
    }
}
// Final ====================================================================


// Funcoes auxiliares/validacao
// ==== FUNCAO PARA VALIDAR CPF ====
int validarCPF(char cpf[]) {

    int soma = 0, resto;
    int dig1, dig2;

    // Verifica tamanho
    if(strlen(cpf) != 11) {
        return 0;
    }

    // Verifica se todos são números
    for(int i = 0; i < 11; i++) {
        if(cpf[i] < '0' || cpf[i] > '9') {
            return 0;
        }
    }

    // Impede CPFs iguais
    int iguais = 1;
    for(int i = 1; i < 11; i++) {
        if(cpf[i] != cpf[0]) {
            iguais = 0;
            break;
        }
    }

    if(iguais) {
        return 0;
    }

    // Primeiro dígito
    soma = 0;
    for(int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }

    resto = (soma * 10) % 11;

    if(resto == 10) {
        resto = 0;
    }

    dig1 = resto;

    // Segundo dígito
    soma = 0;
    for(int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }

    resto = (soma * 10) % 11;

    if(resto == 10) {
        resto = 0;
    }

    dig2 = resto;

    if(dig1 == (cpf[9] - '0') && dig2 == (cpf[10] - '0')) {
        return 1;
    }

    return 0;
}
// Final ======================================================

// ==== FUNCAO PARA CPF DUPLICADO ====
int cpfDuplicado(char cpf[]) {

    for(int i = 0; i < qtdClientes; i++) {
        if(strcmp(clientes[i].cpf, cpf) == 0) {
            return 1;
        }
    }

    return 0;
}
// Final ======================================================

// Funcao que procura um cliente pelo CPF
// Retorna a posicao do cliente no vetor
// Se nao encontrar, retorna -1
int encontrarClientePorCpf(char cpf[]) {

    // Percorre todos os clientes cadastrados
    for(int i = 0; i < qtdClientes; i++) {

        // Compara o CPF digitado com o CPF
        // de cada cliente do vetor
        if(strcmp(clientes[i].cpf, cpf) == 0) {

    // Cliente nao encontrado
    return -1;
}

void salvarClientes() {
    FILE *arq = fopen("clientes.dat", "wb");

    if(arq != NULL) {
        fwrite(&qtdClientes, sizeof(int), 1, arq);
        fwrite(clientes, sizeof(Cliente), qtdClientes, arq);
        fclose(arq);
    }
}

void carregarClientes() {
    FILE *arq = fopen("clientes.dat", "rb");

    if(arq != NULL) {
        fread(&qtdClientes, sizeof(int), 1, arq);
        fread(clientes, sizeof(Cliente), qtdClientes, arq);
        fclose(arq);
    }
}
