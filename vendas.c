#include <stdio.h>
#include <stdlib.h>

void menuVendas() {
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

        switch(opcao) {
            case 1:
                printf("\nIncluir venda\n");
                break;

            case 2:
                printf("\nListar vendas\n");
                break;

            case 0:
                printf("\nVoltando ao menu principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        // Funcao que pede pro usuario clicar enter
        if(opcao != 0) {
            printf("\nPressione enter para continuar...");
            getchar();
            getchar();
        }

    } while(opcao != 0);
}