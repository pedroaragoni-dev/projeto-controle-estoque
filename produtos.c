/*
===========================================================
ARQUIVO: produtos.c

DESCRIÇÃO:
Implementa o módulo de gerenciamento de produtos do
sistema de controle de estoque.

RESPONSABILIDADES:
- Cadastrar produtos;
- Buscar produtos;
- Atualizar estoque;
- Gerar relatórios;
- Realizar exclusão lógica;
- Salvar e carregar produtos em arquivo.
===========================================================
*/


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
int produtosCarregados = 0;

// ==================================
// ===== PROTOTIPOS DAS FUNCOES =====
// ==================================
void menuProdutos();
void incluirProdutos();
void listarProdutos();
void buscarProduto();
void buscarProdutoPorId();
void buscarProdutoPorNome();
void atualizarEstoque();
void calcularValorEstoque();
void relatorioEstoqueBaixo();
void excluirProduto();

void salvarProdutos();
void carregarProdutos();

void limparBuffer();
void pausarSistema();

int nomeDuplicado(char nome[]);
int produtoPossuiVenda(int idProduto);
int encontrarProdutoPorId(int idProduto);


// ================== FUNCAO MENU PRODUTO ==================
void menuProdutos() {

    if(!produtosCarregados) {
        carregarProdutos();
        produtosCarregados = 1;
    }

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
        printf("5 - Calcular valor total do estoque\n");
        printf("6 - Relatorio de estoque baixo\n");
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
                listarProdutos();
                break;
                
            case 3:
                system("cls");
                buscarProduto();
                break;
            case 4:
                system("cls");
                atualizarEstoque();
                break;
            case 5:
                system("cls");
                calcularValorEstoque();
                break;
            case 6:
                system("cls");
                relatorioEstoqueBaixo();
                break;
            case 7:
                system("cls");
                excluirProduto();
                break;
            case 0:
                system("cls");
                printf("\nVoltando...\n");
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
// Final ==========================================================

// ================== 1 - FUNCAO INCLUIR PRODUTO ==================

// Verifica nomes duplicados
// percorre os produtos -> se produto tiver ativo e nome de produto ja estiver em algum
// lugar no vetor (Considerando maiusculas e minusculas) retorna 1, se nao 0
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
    
    // Verifica nome de produto vazio
    if(strlen(produtos[qtdProdutos].nome) == 0) {
        printf(VERMELHO "\nNome invalido\n" RESET);
        return;
    }

    // Se a funcao retornar 1, o produto ja esta cadastrado
    if(nomeDuplicado(produtos[qtdProdutos].nome)) {
        printf(VERMELHO "\nProduto ja cadastrado\n" RESET);
        return;
    }
    
    printf("Quantidade inicial em estoque: ");
    scanf("%d", &produtos[qtdProdutos].quantidade);
    limparBuffer();

    // Verifica se a qtd em estoque informada é menor que 0
    if(produtos[qtdProdutos].quantidade < 0) {
        printf(VERMELHO "\nQuantidade invalida\n" RESET);
        return;
    }

    printf("Preco unitario: R$ ");
    scanf("%f", &produtos[qtdProdutos].preco);
    limparBuffer();

    // Verifica se o preco é <= 0
    if(produtos[qtdProdutos].preco <= 0) {
        printf(VERMELHO "\nPreco Invalido\n" RESET);
        return;
    }

    // Atualiza o id do produto
    produtos[qtdProdutos].id = qtdProdutos + 1; 

    // Coloca produto como ativo
    produtos[qtdProdutos].ativo = 1;

    // Incrementa a quantidade de produtos
    qtdProdutos++;

    // Salva os produtos no arquivo
    salvarProdutos();

    printf(VERDE "\nProduto cadastrado com sucesso!\n" RESET);
}
// Final ====================================================================


// ================== 2 - FUNCAO LISTAR PRODUTO ==================
void listarProdutos() {

    printf("==============================================");
    printf("\n============= LISTA DE PRODUTOS ==============\n");
    printf("==============================================\n");

    // Variável para guardar Ativo / Deletado
    char status[30];

    // Verifica se há produtos existentes
    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    // Cabeçalho reservando espaços
    printf("\n============================================================\n");
    printf("%-5s %-20s %-12s %-12s %-15s\n",
            "ID", "Nome", "Quantidade", "Preco", "Status");
    printf("============================================================\n");

    // Loop para imprimir os produtos
    for(int i=0; i < qtdProdutos; i++) {

        // Condicao para substituir o numero para uma string, ficando melhor visualmente
        if(produtos[i].ativo == 0) {
            strcpy(status, "DELETADO");
        }
        else if(produtos[i].quantidade == 0) {
            strcpy(status, "SEM ESTOQUE");
        }
        else {
            strcpy(status, "ATIVO");
        }

        // Reservando espaços 
        printf("%-5d %-20s %-12d %-12.2f %-15s\n", 
            produtos[i].id,
            produtos[i].nome,
            produtos[i].quantidade,
            produtos[i].preco,
            status);
    }
}
// Final =========================================================

// ===================== 3 - FUNCAO BUSCAR PRODUTO =====================
void buscarProduto() {

    int opcao;

    // Verifica se há produtos existentes
    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }else {
        do {
            system("cls");

            printf("===============================================");
            printf("\n=============== BUSCAR PRODUTO ================\n");
            printf("===============================================\n");

            printf("\n1 - Buscar por ID");
            printf("\n2 - Buscar por nome");
            printf("\n0 - Voltar\n");

            printf("\nEscolha uma opcao: ");
            scanf("%d", &opcao);
            limparBuffer();

            switch (opcao) {

                case 1:
                    system("cls");
                    buscarProdutoPorId();
                break;

                case 2:
                    system("cls");
                    buscarProdutoPorNome();
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
}

// Funcao de buscar produto por ID
void buscarProdutoPorId() {

    int encontrou = 0;
    int posicao = -1;
    int idDigitado;

    printf("Digite o ID: ");
    scanf("%d", &idDigitado);
    limparBuffer();

    // Loop para encontrar o id
    for(int i = 0; i < qtdProdutos; i++) {

        if(produtos[i].id == idDigitado) {
            encontrou = 1;
            posicao = i;
            break;
        }
    }

    // Se encontrar, mostrar tudo sobre o produto
    if(encontrou == 1) {
        printf(VERDE "PRODUTO ENCONTRADO\n" RESET);

        printf("------------------------------------\n");
        printf("ID: %d", produtos[posicao].id);
        printf("\nNome: %s", produtos[posicao].nome);
        printf("\nQuantidade: %d", produtos[posicao].quantidade);
        printf("\nPreco unitario: R$ %.2f", produtos[posicao].preco);
        
        if(produtos[posicao].ativo == 1) {
            printf("\nStatus: ATIVO");
        }
        else {
            printf("\nStatus: DELETADO");
        }

        printf("\n------------------------------------\n");
    }
    else {
        printf(VERMELHO "PRODUTO NAO ENCONTRADO\n" RESET);
    }
}

// Funcao para encontrar o produto por partes do nome
void buscarProdutoPorNome() {

    int encontrou = 0;
    // Variavel para salvar o nome da busca do usuario
    char nomeBusca[TAM_NOME_PRODUTO];

    printf("Digite parte do nome: ");
    fgets(nomeBusca, TAM_NOME_PRODUTO, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Validacao para busca vazia
    if(strlen(nomeBusca) == 0) {
        printf(VERMELHO "\nBusca invalida!\n" RESET);
        return;
    }

    printf("\nResultado:\n");

    // Loop para mostrar todos os produtos que relacionam-se com a busca
    // Ex: Busca: Mo / Resultado: Monitor, Mouse, Mo...
    for(int i = 0; i < qtdProdutos; i++) {

        // Variavel cópia do nome do produto
        char nomeProduto[TAM_NOME_PRODUTO];

        // Variavel cópia do nome da busca
        char busca[TAM_NOME_PRODUTO];

        // Copiando os nomes de produto e busca para as variaveis cópias para conversao
        strcpy(nomeProduto, produtos[i].nome);
        strcpy(busca, nomeBusca);

        // Converte o nome do produto para minúsculo
        for(int j = 0; nomeProduto[j] != '\0'; j++) {
            nomeProduto[j] = tolower(nomeProduto[j]);
        }

        // Converte a busca para minúsculo
        for(int j = 0; busca[j] != '\0'; j++) {
            busca[j] = tolower(busca[j]);
        }

        // Procura se a parte digitada pelo usuário está contida
        // no nome do produto. Como as duas strings foram convertidas
        // para minúsculo anteriormente, a busca ignora diferenças
        // entre letras maiúsculas e minúsculas.
        // Exemplo:
        // Produto: "Mouse Gamer"
        // Busca: "mou", "MOU" ou "Mou"
        // Todas as buscas serão encontradas.
        if(strstr(nomeProduto, busca) != NULL) {
            encontrou = 1; 
            
            printf("------------------------------------\n");
            printf("ID: %d", produtos[i].id);
            printf("\nNome: %s", produtos[i].nome);
            printf("\nQuantidade: %d", produtos[i].quantidade);
            printf("\nPreco unitario: R$ %.2f", produtos[i].preco);
            
            if(produtos[i].ativo == 1) {
                printf("\nStatus: ATIVO");
            }
            else {
                printf("\nStatus: DELETADO");
            }
            printf("\n------------------------------------\n");
        }
    }

    if(encontrou == 0) {

        printf(VERMELHO "\n=== PRODUTO NAO LOCALIZADO ===\n" RESET);
    }
} 
// Final =========================================================

// ===================== FUNCAO ATUALIZAR ESTOQUE =====================

void atualizarEstoque() {

    int idDigitado;
    int quantidade;
    int opcao;
    int encontrou = 0;
    int posicao = -1;

    printf("==============================================");
    printf("\n============ ATUALIZAR ESTOQUE ===============\n");
    printf("==============================================\n");

    // Verifica se existe pelo menos um produto cadastrado
    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    // Solicita o ID do produto que terá o estoque alterado
    printf("\nDigite o ID do produto: ");
    scanf("%d", &idDigitado);
    limparBuffer();

    // Percorre o vetor procurando o produto pelo ID
    for(int i = 0; i < qtdProdutos; i++) {
        if(produtos[i].id == idDigitado) {
            encontrou = 1;
            posicao = i;
            break;
        }
    }

    // Se não encontrou o ID informado, encerra a função
    if(encontrou == 0) {
        printf(VERMELHO "\nProduto nao localizado!\n" RESET);
        return;
    }

    // Produtos deletados não devem ter estoque alterado
    if(produtos[posicao].ativo == 0) {
        printf(VERMELHO "\nProduto deletado. Nao e possivel atualizar o estoque!\n" RESET);
        return;
    }

    // Mostra informações básicas para confirmar o produto encontrado
    printf("\nProduto encontrado: %s", produtos[posicao].nome);
    printf("\nEstoque atual: %d\n", produtos[posicao].quantidade);

    printf("\n1 - Entrada no estoque");
    printf("\n2 - Saida do estoque\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);
    limparBuffer();

    // Solicita a quantidade que será adicionada ou retirada
    printf("\nQuantidade: ");
    scanf("%d", &quantidade);
    limparBuffer();

    // Não permite quantidade zero ou negativa
    if(quantidade <= 0) {
        printf(VERMELHO "\nQuantidade invalida!\n" RESET);
        return;
    }

    // Entrada: soma a quantidade ao estoque
    if(opcao == 1) {
        produtos[posicao].quantidade += quantidade;

        // Salva a alteracao no arquivo
        salvarProdutos();

        printf(VERDE "\nEntrada realizada com sucesso!\n" RESET);
        printf("Novo estoque: %d\n", produtos[posicao].quantidade);
    }

    // Saída: subtrai a quantidade do estoque
    else if(opcao == 2) {

        // Impede que o estoque fique negativo
        if(produtos[posicao].quantidade - quantidade < 0) {
            printf(VERMELHO "\nEstoque insuficiente!\n" RESET);
            printf("Estoque atual: %d\n", produtos[posicao].quantidade);
            return;
        }

        produtos[posicao].quantidade -= quantidade;

        // Salva a alteracao no arquivo
        salvarProdutos();

        printf(VERDE "\nSaida realizada com sucesso!\n" RESET);
        printf("Novo estoque: %d\n", produtos[posicao].quantidade);
    }

    // Caso o usuário escolha uma opção diferente de 1 ou 2
    else {
        printf(VERMELHO "\nOpcao invalida!\n" RESET);
    }
}
// Final ==========================================================

// ============= FUNCAO PRA CALCULAR VALOR TOTAL DO ESTOQUE =============
void calcularValorEstoque() {

    // Variável acumuladora que armazenará
    // o valor total de todos os produtos ativos
    float valorTotal = 0;

    printf("==============================================");
    printf("\n======= VALOR TOTAL DO ESTOQUE ===============\n");
    printf("==============================================\n");

    // Verifica se existe pelo menos um produto cadastrado
    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    // Percorre todos os produtos cadastrados
    for(int i = 0; i < qtdProdutos; i++) {

        // Produtos deletados não entram no cálculo
        if(produtos[i].ativo == 1) {

            // Soma ao total o valor de cada produto:
            // valor do produto = quantidade em estoque × preço unitário
            valorTotal += produtos[i].quantidade * produtos[i].preco;
        }
    }

    printf(VERDE "\nValor total do estoque: R$ %.2f\n" RESET, valorTotal);
}
// Final ===================================================================

// ================== FUNCAO DE RELATORIO DE ESTOQUE BAIXO ==================
void relatorioEstoqueBaixo() {

    int encontrou = 0;
    int limite;

    printf("==============================================");
    printf("\n========== RELATORIO DE ESTOQUE BAIXO ========\n");
    printf("==============================================\n");

    // Verifica se existe pelo menos um produto
    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    printf("\nInforme o limite minimo de estoque: ");
    scanf("%d", &limite);
    limparBuffer();

    if(limite < 0) {
        printf(VERMELHO "\nLimite invalido!\n" RESET);
        return;
    }

    printf("\nProdutos com estoque igual ou inferior a %d unidades:\n", limite);

    // Percorre todos os produtos cadastrados
    for(int i = 0; i < qtdProdutos; i++) {

        // Mostra somente produtos ativos
        // com quantidade menor ou igual ao limite dito pelo usuario
        if(produtos[i].ativo == 1 && produtos[i].quantidade <= limite) {

            encontrou = 1;

            printf("------------------------------------\n");
            printf("ID: %d", produtos[i].id);
            printf("\nNome: %s", produtos[i].nome);
            printf("\nQuantidade: %d", produtos[i].quantidade);
            printf("\nPreco unitario: R$ %.2f", produtos[i].preco);
            printf("\nStatus: ESTOQUE BAIXO");
            printf("\n------------------------------------\n");
        }
    }

    // Caso nenhum produto tenha estoque baixo
    if(encontrou == 0) {
        printf(VERDE "\nNenhum produto com estoque baixo.\n" RESET);
    }
}
// Final ===================================================================

// ======================= FUNCAO DE EXCLUIR PRODUTO =======================
void excluirProduto() {

    int idDigitado;
    int encontrou = 0;
    int posicao = -1;

    printf("==============================================");
    printf("\n============= EXCLUIR PRODUTO ================\n");
    printf("==============================================\n");

    // Verifica se existe pelo menos um produto
    if(qtdProdutos == 0) {
        printf(VERMELHO "\nNenhum produto cadastrado!\n" RESET);
        return;
    }

    printf("\nDigite o ID do produto: ");
    scanf("%d", &idDigitado);
    limparBuffer();

    // Procura o produto pelo ID
    for(int i = 0; i < qtdProdutos; i++) {
        if(produtos[i].id == idDigitado) {
            encontrou = 1;
            posicao = i;
            break;
        }
    }

    // Produto não encontrado
    if(encontrou == 0) {
        printf(VERMELHO "\nProduto nao localizado!\n" RESET);
        return;
    }

    // Produto já deletado
    if(produtos[posicao].ativo == 0) {
        printf(VERMELHO "\nEste produto ja esta deletado!\n" RESET);
        return;
    }

    // Verifica se existe venda vinculada
    if(produtoPossuiVenda(idDigitado)) {
        printf(VERMELHO "\nNao e possivel excluir este produto.\n"
            "Existem vendas vinculadas ao historico.\n" RESET);
        return;
    }

    // Exclusão lógica
    produtos[posicao].ativo = 0;

    // Salva a alteracao no arquivo
    salvarProdutos();

    printf(VERDE "\nProduto deletado com sucesso!\n" RESET);
}
// Final =====================================================

// Funcao que procura um produto pelo ID
// Retorna a posicao do produto no vetor
// Se nao encontrar, retorna -1
int encontrarProdutoPorId(int idProduto) {

    // Percorre todos os produtos cadastrados
    for(int i = 0; i < qtdProdutos; i++) {

        // Verifica se o ID do produto atual
        // é igual ao ID informado
        if(produtos[i].id == idProduto) {
            return i; // retorna a posicao encontrada
        }
    }

    // Produto nao encontrado
    return -1;
}

/*
    A função salvarProdutos() abre um arquivo binário e grava primeiro a quantidade de produtos cadastrados e depois o vetor de produtos. Já a função carregarProdutos() faz o processo inverso: lê a quantidade de produtos e depois lê o vetor, reconstruindo os dados em memória quando o programa é iniciado.
*/

// ================== SALVAR PRODUTOS ==================
void salvarProdutos() {

    FILE *arq = fopen("produtos.dat", "wb");

    if(arq != NULL) {
        fwrite(&qtdProdutos, sizeof(int), 1, arq);
        fwrite(produtos, sizeof(Produto), qtdProdutos, arq);

        fclose(arq);
    }
}

// ================== CARREGAR PRODUTOS ==================
void carregarProdutos() {

    FILE *arq = fopen("produtos.dat", "rb");

    if(arq != NULL) {
        fread(&qtdProdutos, sizeof(int), 1, arq);
        fread(produtos, sizeof(Produto), qtdProdutos, arq);

        fclose(arq);
    }
}
