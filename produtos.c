#include <stdio.h>
#include <stdlib.h>

void menuProdutos() {
    int opcao;

    do {
        system("cls");

        printf("======================================");
        printf("\n============== PRODUTOS ==============\n");
        printf("======================================\n");

        printf("\n1 - Incluir produto\n");
        printf("2 - Excluir produto\n");
        printf("3 - Listar produtos\n");
        printf("4 - Atualizar estoque\n");
        printf("5 - Buscar produto\n");
        printf("6 - Calcular valor total do estoque\n");
        printf("7 - Relatorio de estoque baixo\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nIncluir produto\n");
                break;
            case 2:
                printf("\nExcluir produto\n");
                break;
            case 3:
                printf("\nListar produtos\n");
                break;
            case 4:
                printf("\nAtualizar estoque\n");
                break;
            case 5:
                printf("\nBuscar produto\n");
                break;
            case 6:
                printf("\nCalcular valor total do estoque\n");
                break;
            case 7:
                printf("\nRelatorio de estoque baixo\n");
                break;
            case 0:
                printf("\nVoltando...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }

    } while(opcao != 0);
}