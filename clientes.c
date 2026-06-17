#include <stdio.h>
#include <stdlib.h>

void menuClientes() {
    int opcao;

    do {
        system("cls");

        printf("======================================");
        printf("\n============== CLIENTES ==============\n");
        printf("======================================\n");

        printf("\n1 - Incluir cliente\n");
        printf("2 - Listar clientes\n");
        printf("0 - Voltar\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("\nIncluir cliente\n");
                break;

            case 2:
                printf("\nListar clientes\n");
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