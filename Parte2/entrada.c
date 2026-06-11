#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrada.h"

static int ler_linha(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) == NULL) {
        return 0;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    return 1;
}

static void trocar_virgula_por_ponto(char *texto) {
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }
}

static int terminou_com_espacos(const char *texto) {
    while (*texto != '\0') {
        if (!isspace((unsigned char)*texto)) {
            return 0;
        }
        texto++;
    }

    return 1;
}

int ler_int(const char *mensagem) {
    char buffer[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        if (!ler_linha(buffer, sizeof(buffer))) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        errno = 0;
        valor = strtol(buffer, &fim, 10);

        if (fim != buffer && errno == 0 && terminou_com_espacos(fim)) {
            return (int)valor;
        }

        printf("Digite um numero inteiro valido.\n");
    }
}

int ler_texto(const char *mensagem, char *buffer, int tamanho) {
    printf("%s", mensagem);
    return ler_linha(buffer, tamanho);
}

double ler_double_maior_que(const char *mensagem, double minimo) {
    char buffer[100];
    char *fim;
    double valor;

    while (1) {
        printf("%s", mensagem);

        if (!ler_linha(buffer, sizeof(buffer))) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        trocar_virgula_por_ponto(buffer);
        errno = 0;
        valor = strtod(buffer, &fim);

        if (fim != buffer && errno == 0 && terminou_com_espacos(fim) && valor > minimo) {
            return valor;
        }

        printf("Digite um valor maior que %.6f.\n", minimo);
    }
}

double ler_double_positivo(const char *mensagem) {
    return ler_double_maior_que(mensagem, 0.0);
}

int ler_opcao_menu(const char *mensagem, int minimo, int maximo) {
    int opcao;

    while (1) {
        opcao = ler_int(mensagem);

        if (opcao >= minimo && opcao <= maximo) {
            return opcao;
        }

        printf("Opcao invalida. Escolha entre %d e %d.\n", minimo, maximo);
    }
}
