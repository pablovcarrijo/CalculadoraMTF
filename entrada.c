#include <stdio.h>
#include <string.h>

#include "entrada.h"

void limparBuffer(void)
{
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

int lerInteiro(const char *mensagem)
{
    int valor;
    int leitura;

    do {
        printf("%s", mensagem);
        leitura = scanf("%d", &valor);

        if (leitura != 1) {
            printf("Entrada invalida. Digite um numero inteiro.\n");
            limparBuffer();
        }
    } while (leitura != 1);

    limparBuffer();
    return valor;
}

double lerDouble(const char *mensagem)
{
    double valor;
    int leitura;

    do {
        printf("%s", mensagem);
        leitura = scanf("%lf", &valor);

        if (leitura != 1) {
            printf("Entrada invalida. Digite um numero valido.\n");
            limparBuffer();
        }
    } while (leitura != 1);

    limparBuffer();
    return valor;
}

double lerTaxaPercentual(const char *mensagem)
{
    double taxaPercentual = lerDouble(mensagem);
    return taxaPercentual / 100.0;
}

double lerTaxaAoDia(const char *mensagem)
{
    double taxa;
    char unidade[20];
    int leitura;

    do {
        printf("%s", mensagem);
        printf("Exemplos: 1%%a.d, 1%%a.m ou 1%%a.a\n");
        leitura = scanf("%lf%19s", &taxa, unidade);

        if (leitura != 2) {
            printf("Entrada invalida. Digite no formato 1%%a.a.\n");
            limparBuffer();
        } else if (strcmp(unidade, "%a.d") != 0 &&
                   strcmp(unidade, "%a.m") != 0 &&
                   strcmp(unidade, "%a.a") != 0) {
            printf("Unidade invalida. Use %%a.d, %%a.m ou %%a.a.\n");
            leitura = 0;
            limparBuffer();
        }
    } while (leitura != 2);

    limparBuffer();
    taxa = taxa / 100.0;

    if (strcmp(unidade, "%a.m") == 0) {
        taxa = taxa / 30.0;
    } else if (strcmp(unidade, "%a.a") == 0) {
        taxa = taxa / 360.0;
    }

    return taxa;
}

double lerTempoEmDias(const char *mensagem)
{
    double tempo;
    char unidade[20];
    int leitura;

    do {
        printf("%s", mensagem);
        printf("Exemplos: 10 dias, 10 meses ou 10 anos\n");
        leitura = scanf("%lf%19s", &tempo, unidade);

        if (leitura != 2) {
            printf("Entrada invalida. Digite no formato 10 anos.\n");
            limparBuffer();
        } else if (strcmp(unidade, "dia") != 0 &&
                   strcmp(unidade, "dias") != 0 &&
                   strcmp(unidade, "mes") != 0 &&
                   strcmp(unidade, "meses") != 0 &&
                   strcmp(unidade, "ano") != 0 &&
                   strcmp(unidade, "anos") != 0) {
            printf("Unidade invalida. Use dias, meses ou anos.\n");
            leitura = 0;
            limparBuffer();
        }
    } while (leitura != 2);

    limparBuffer();

    if (strcmp(unidade, "mes") == 0 || strcmp(unidade, "meses") == 0) {
        tempo = tempo * 30.0;
    } else if (strcmp(unidade, "ano") == 0 || strcmp(unidade, "anos") == 0) {
        tempo = tempo * 360.0;
    }

    return tempo;
}

void pausar(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}
