#include <stdio.h>

#include "menus.h"

void mostrarMenuPrincipal(void)
{
    printf("\n=============================================\n");
    printf(" Calculadora Financeira - Capitalizacao Simples\n");
    printf("=============================================\n");
    printf("1. Calcular Juros (J)\n");
    printf("2. Calcular Montante / Valor Futuro (VF)\n");
    printf("3. Calcular Capital / Valor Presente (VP)\n");
    printf("4. Calcular Taxa (i)\n");
    printf("5. Calcular Tempo (n)\n");
    printf("6. Calcular taxa efetiva a partir da taxa de desconto comercial\n");
    printf("7. Calcular taxa de desconto comercial a partir da taxa efetiva\n");
    printf("0. Sair\n");
    printf("=============================================\n");
}
