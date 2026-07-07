/*
===========================================================
PROJETO: Sistema de Controle de Estoque
DISCIPLINA: Algoritmos e Programação / Linguagem C
CURSO: Tecnologia em Sistemas para Internet (TSI)
INSTITUIÇÃO: IFSP - Campus Araraquara

PROGRAMADORES:
- Pedro
- Ryan 

DATA: 26/06/2026

OBJETIVO:
Desenvolver um sistema de controle de estoque utilizando
a linguagem C, permitindo o gerenciamento de produtos,
clientes e vendas. O sistema possibilita cadastrar,
consultar, atualizar e listar informações, além de
registrar vendas e realizar persistência dos dados em
arquivos.

FUNCIONALIDADES:
- Cadastro de produtos;
- Busca de produtos por ID e por nome;
- Atualização de estoque;
- Relatório de estoque baixo;
- Exclusão lógica de produtos;
- Cadastro de clientes;
- Validação oficial de CPF;
- Controle do total de vendas por cliente;
- Cadastro e listagem de vendas;
- Controle automático de estoque após vendas;
- Persistência de dados em arquivos binários.

OBSERVAÇÕES:
O projeto foi desenvolvido de forma modular, sendo
dividido em arquivos específicos para cada módulo
(produtos, clientes e vendas), visando maior organização,
legibilidade e manutenção do código.
===========================================================
*/

// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include "produtos.c"
#include "clientes.c"
#include "vendas.c"

// DEFINICOES DE CORES
#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define RESET "\033[0m"

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

    system("cls"); // Limpar a tela no início

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
                printf(VERDE "\nEncerrando o programa...\n" RESET);
                break;

            default:
                system("cls");
                printf(VERMELHO "\nOpcao invalida! Tente novamente.\n" RESET);
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            pausarSistema();
        }
    } while(opcao != 0);

    return 0;
}