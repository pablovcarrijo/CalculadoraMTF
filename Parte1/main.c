#include <stdio.h>

#include "calculos.h"
#include "entrada.h"
#include "menus.h"

int main(void)
{
    int opcao;
    double vp, vf, j, i, ic, n, resultado;

    do
    {
        mostrarMenuPrincipal();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao)
        {
        case 1:
            vf = lerDouble("Informe o Montante / Valor Futuro (VF): ");
            i = lerTaxaAoDia("Informe a taxa (i) em porcentagem: ");
            n = lerTempoEmDias("Informe o tempo (n): ");

            if (1.0 + i * n == 0.0)
            {
                printf("\nErro: nao e possivel dividir por zero.\n");
            }
            else
            {
                resultado = calcularValorPresente(vf, i, n);
                printf("\nCapital / Valor Presente (VP): %.2f\n", resultado);
                printf("Taxa usada no calculo: %.2f%% ao dia\n", i * 100.0);
                printf("Tempo usado no calculo: %.0f dias\n", n);
            }

            pausar();
            break;
        case 2:
            vp = lerDouble("Informe o Capital / Valor Presente (VP): ");
            i = lerTaxaAoDia("Informe a taxa (i) em porcentagem: ");
            n = lerTempoEmDias("Informe o tempo (n): ");

            resultado = calcularMontante(vp, i, n);
            printf("\nMontante / Valor Futuro (VF): %.2f\n", resultado);
            printf("Taxa usada no calculo: %.2f%% ao dia\n", i * 100.0);
            printf("Tempo usado no calculo: %.0f dias\n", n);
            pausar();
            break;

        case 3:
            vp = lerDouble("Informe o Capital / Valor Presente (VP): ");
            i = lerTaxaAoDia("Informe a taxa (i) em porcentagem: ");
            n = lerTempoEmDias("Informe o tempo (n): ");

            resultado = calcularJuros(vp, i, n);
            printf("\nJuros (J): %.2f\n", resultado);
            printf("Taxa usada no calculo: %.2f%% ao dia\n", i * 100.0);
            printf("Tempo usado no calculo: %.0f dias\n", n);
            pausar();
            break;

        case 4:
            j = lerDouble("Informe os Juros (J): ");
            vp = lerDouble("Informe o Capital / Valor Presente (VP): ");
            n = lerTempoEmDias("Informe o tempo (n): ");

            if (vp == 0.0 || n == 0.0)
            {
                printf("\nErro: VP e n devem ser diferentes de zero.\n");
            }
            else
            {
                resultado = calcularTaxa(j, vp, n);
                printf("\nTaxa diaria (i): %.2f%% ao dia\n", resultado * 100.0);
                printf("Tempo usado no calculo: %.0f dias\n", n);
            }

            pausar();
            break;

        case 5:
            j = lerDouble("Informe os Juros (J): ");
            vp = lerDouble("Informe o Capital / Valor Presente (VP): ");
            i = lerTaxaAoDia("Informe a taxa (i) em porcentagem: ");

            if (vp == 0.0 || i == 0.0)
            {
                printf("\nErro: VP e i devem ser diferentes de zero.\n");
            }
            else
            {
                resultado = calcularTempo(j, vp, i);
                printf("\nTempo (n): %.0f dias\n", resultado);
                printf("Taxa usada no calculo: %.2f%% ao dia\n", i * 100.0);
            }

            pausar();
            break;

        case 6:
            ic = lerTaxaAoDia("Informe a taxa de desconto comercial (ic) em porcentagem: ");
            n = lerTempoEmDias("Informe o tempo (n): ");

            if (1.0 - ic * n == 0.0)
            {
                printf("\nErro: nao e possivel dividir por zero.\n");
            }
            else
            {
                resultado = calcularTaxaEfetiva(ic, n);
                printf("\nTaxa efetiva diaria (i): %.2f%% ao dia\n", resultado * 100.0);
                printf("Tempo usado no calculo: %.0f dias\n", n);
            }

            pausar();
            break;

        case 7:
            i = lerTaxaAoDia("Informe a taxa efetiva (i) em porcentagem: ");
            n = lerTempoEmDias("Informe o tempo (n): ");

            if (1.0 + i * n == 0.0)
            {
                printf("\nErro: nao e possivel dividir por zero.\n");
            }
            else
            {
                resultado = calcularTaxaComercial(i, n);
                printf("\nTaxa de desconto comercial diaria (ic): %.2f%% ao dia\n", resultado * 100.0);
                printf("Tempo usado no calculo: %.0f dias\n", n);
            }

            pausar();
            break;

        case 0:
            printf("\nEncerrando a calculadora...\n");
            break;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
            pausar();
            break;
        }
    } while (opcao != 0);

    return 0;
}
