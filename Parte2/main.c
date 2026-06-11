#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entrada.h"
#include "financeira.h"
#include "unidades.h"

static int identificar_unidade_taxa(const char *texto, UnidadeTempo *unidade) {
    char normalizado[30];
    int i;
    int j = 0;

    for (i = 0; texto[i] != '\0' && j < (int)sizeof(normalizado) - 1; i++) {
        if (!isspace((unsigned char)texto[i]) && texto[i] != '.') {
            normalizado[j] = (char)tolower((unsigned char)texto[i]);
            j++;
        }
    }
    normalizado[j] = '\0';

    if (strcmp(normalizado, "ad") == 0 || strcmp(normalizado, "aodia") == 0) {
        *unidade = UNIDADE_DIA;
        return 1;
    }

    if (strcmp(normalizado, "am") == 0 || strcmp(normalizado, "aomes") == 0) {
        *unidade = UNIDADE_MES;
        return 1;
    }

    if (strcmp(normalizado, "aa") == 0 || strcmp(normalizado, "aoano") == 0) {
        *unidade = UNIDADE_ANO;
        return 1;
    }

    if (strcmp(normalizado, "as") == 0 || strcmp(normalizado, "aosemestre") == 0) {
        *unidade = UNIDADE_SEMESTRE;
        return 1;
    }

    if (strcmp(normalizado, "ab") == 0 || strcmp(normalizado, "aobimestre") == 0) {
        *unidade = UNIDADE_BIMESTRE;
        return 1;
    }

    if (strcmp(normalizado, "at") == 0 || strcmp(normalizado, "aotrimestre") == 0) {
        *unidade = UNIDADE_TRIMESTRE;
        return 1;
    }

    return 0;
}

static int identificar_unidade_tempo_texto(const char *texto, UnidadeTempo *unidade) {
    char normalizado[30];
    int i;
    int j = 0;

    for (i = 0; texto[i] != '\0' && j < (int)sizeof(normalizado) - 1; i++) {
        if (!isspace((unsigned char)texto[i]) && texto[i] != '.') {
            normalizado[j] = (char)tolower((unsigned char)texto[i]);
            j++;
        }
    }
    normalizado[j] = '\0';

    if (strcmp(normalizado, "d") == 0 || strcmp(normalizado, "dia") == 0 ||
        strcmp(normalizado, "dias") == 0 || strcmp(normalizado, "diario") == 0 ||
        strcmp(normalizado, "diaria") == 0 || strcmp(normalizado, "pordia") == 0) {
        *unidade = UNIDADE_DIA;
        return 1;
    }

    if (strcmp(normalizado, "m") == 0 || strcmp(normalizado, "mes") == 0 ||
        strcmp(normalizado, "meses") == 0 || strcmp(normalizado, "mensal") == 0) {
        *unidade = UNIDADE_MES;
        return 1;
    }

    if (strcmp(normalizado, "a") == 0 || strcmp(normalizado, "ano") == 0 ||
        strcmp(normalizado, "anos") == 0 || strcmp(normalizado, "anual") == 0) {
        *unidade = UNIDADE_ANO;
        return 1;
    }

    if (strcmp(normalizado, "s") == 0 || strcmp(normalizado, "semestre") == 0 ||
        strcmp(normalizado, "semestres") == 0 || strcmp(normalizado, "semestral") == 0) {
        *unidade = UNIDADE_SEMESTRE;
        return 1;
    }

    if (strcmp(normalizado, "b") == 0 || strcmp(normalizado, "bimestre") == 0 ||
        strcmp(normalizado, "bimestres") == 0 || strcmp(normalizado, "bimestral") == 0) {
        *unidade = UNIDADE_BIMESTRE;
        return 1;
    }

    if (strcmp(normalizado, "t") == 0 || strcmp(normalizado, "trimestre") == 0 ||
        strcmp(normalizado, "trimestres") == 0 || strcmp(normalizado, "trimestral") == 0) {
        *unidade = UNIDADE_TRIMESTRE;
        return 1;
    }

    return 0;
}

static void trocar_virgula_por_ponto(char *texto) {
    int i;

    for (i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ',') {
            texto[i] = '.';
        }
    }
}

static double ler_taxa_com_unidade(const char *mensagem, UnidadeTempo *unidade) {
    char buffer[100];
    char *fim_numero;
    double taxa_percentual;

    while (1) {
        if (!ler_texto(mensagem, buffer, sizeof(buffer))) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        trocar_virgula_por_ponto(buffer);
        errno = 0;
        taxa_percentual = strtod(buffer, &fim_numero);

        if (fim_numero == buffer || errno != 0 || taxa_percentual <= -100.0) {
            printf("Digite uma taxa maior que -100%%. Exemplo: 5%% a.m.\n");
            continue;
        }

        while (isspace((unsigned char)*fim_numero)) {
            fim_numero++;
        }

        if (*fim_numero == '%') {
            fim_numero++;
        }

        while (isspace((unsigned char)*fim_numero)) {
            fim_numero++;
        }

        if (identificar_unidade_taxa(fim_numero, unidade)) {
            return taxa_percentual / 100.0;
        }

        printf("Informe a unidade da taxa. Exemplos: 5%% a.d., 5%% a.m., 5%% a.b., 5%% a.t., 5%% a.s. ou 5%% a.a.\n");
    }
}

static double ler_tempo_com_unidade(const char *mensagem, UnidadeTempo *unidade) {
    char buffer[100];
    char *fim_numero;
    double tempo;

    while (1) {
        if (!ler_texto(mensagem, buffer, sizeof(buffer))) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        trocar_virgula_por_ponto(buffer);
        errno = 0;
        tempo = strtod(buffer, &fim_numero);

        if (fim_numero == buffer || errno != 0 || tempo <= 0.0) {
            printf("Digite um tempo maior que zero. Exemplo: 2 anos.\n");
            continue;
        }

        while (isspace((unsigned char)*fim_numero)) {
            fim_numero++;
        }

        if (identificar_unidade_tempo_texto(fim_numero, unidade)) {
            return tempo;
        }

        printf("Informe a unidade do tempo. Exemplos: 30 dias, 5 meses, 1 bimestre, 1 trimestre, 1 semestre ou 2 anos.\n");
    }
}

static UnidadeTempo ler_periodo(const char *mensagem) {
    char buffer[100];
    UnidadeTempo unidade;

    while (1) {
        if (!ler_texto(mensagem, buffer, sizeof(buffer))) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        if (identificar_unidade_tempo_texto(buffer, &unidade)) {
            return unidade;
        }

        printf("Informe um periodo valido: por dia, mensal, bimestral, trimestral, semestral ou anual.\n");
    }
}

static void imprimir_resultado_financeiro(double valor_presente, double valor_futuro,
                                          double taxa, UnidadeTempo unidade_taxa,
                                          double periodos) {
    printf("\n===== Resultado =====\n");
    printf("Capital (VP): R$ %.2f\n", valor_presente);
    printf("Montante (VF): R$ %.2f\n", valor_futuro);
    printf("Juros (J): R$ %.2f\n", calcular_juros(valor_presente, valor_futuro));
    printf("Taxa usada: %.6f%% %s\n", taxa * 100.0, nome_taxa(unidade_taxa));
    printf("Tempo usado: %.6f %s\n", periodos, nome_unidade_plural(unidade_taxa));
    printf("=====================\n\n");
}

static void calcular_vp_menu(void) {
    double valor_futuro = ler_double_positivo("Informe o VF: R$ ");
    UnidadeTempo unidade_taxa;
    double taxa = ler_taxa_com_unidade("Informe a taxa (ex: 5% a.m.): ", &unidade_taxa);
    UnidadeTempo unidade_tempo;
    double tempo = ler_tempo_com_unidade("Informe o tempo (ex: 2 anos): ", &unidade_tempo);
    double periodos = calcular_periodos(tempo, unidade_tempo, unidade_taxa);
    double valor_presente = calcular_valor_presente(valor_futuro, taxa, periodos);

    imprimir_resultado_financeiro(valor_presente, valor_futuro, taxa, unidade_taxa, periodos);
}

static void calcular_vf_menu(void) {
    double valor_presente = ler_double_positivo("Informe o VP: R$ ");
    UnidadeTempo unidade_taxa;
    double taxa = ler_taxa_com_unidade("Informe a taxa (ex: 5% a.m.): ", &unidade_taxa);
    UnidadeTempo unidade_tempo;
    double tempo = ler_tempo_com_unidade("Informe o tempo (ex: 3 meses): ", &unidade_tempo);
    double periodos = calcular_periodos(tempo, unidade_tempo, unidade_taxa);
    double valor_futuro = calcular_valor_futuro(valor_presente, taxa, periodos);

    imprimir_resultado_financeiro(valor_presente, valor_futuro, taxa, unidade_taxa, periodos);
}

static void calcular_juros_menu(void) {
    double valor_presente = ler_double_positivo("Informe o VP: R$ ");
    UnidadeTempo unidade_taxa;
    double taxa = ler_taxa_com_unidade("Informe a taxa (ex: 5% a.m.): ", &unidade_taxa);
    UnidadeTempo unidade_tempo;
    double tempo = ler_tempo_com_unidade("Informe o tempo (ex: 3 meses): ", &unidade_tempo);
    double periodos = calcular_periodos(tempo, unidade_tempo, unidade_taxa);
    double valor_futuro = calcular_valor_futuro(valor_presente, taxa, periodos);

    imprimir_resultado_financeiro(valor_presente, valor_futuro, taxa, unidade_taxa, periodos);
}

static void calcular_taxa_menu(void) {
    double valor_presente = ler_double_positivo("Informe o VP: R$ ");
    double valor_futuro = ler_double_positivo("Informe o VF: R$ ");
    UnidadeTempo unidade_tempo;
    double tempo = ler_tempo_com_unidade("Informe o tempo (ex: 6 meses): ", &unidade_tempo);
    UnidadeTempo unidade_resposta = ler_unidade_tempo("Unidade desejada para a taxa:");
    double periodos = calcular_periodos(tempo, unidade_tempo, unidade_resposta);
    double taxa;

    if (periodos == 0.0 || valor_futuro / valor_presente <= 0.0) {
        printf("Nao foi possivel calcular a taxa com os dados informados.\n\n");
        return;
    }

    taxa = calcular_taxa(valor_presente, valor_futuro, periodos);

    printf("\n===== Resultado =====\n");
    printf("Taxa encontrada: %.6f%% %s\n", taxa * 100.0, nome_taxa(unidade_resposta));
    printf("=====================\n\n");
}

static void calcular_tempo_menu(void) {
    double valor_presente = ler_double_positivo("Informe o VP: R$ ");
    double valor_futuro = ler_double_positivo("Informe o VF: R$ ");
    UnidadeTempo unidade_taxa;
    double taxa = ler_taxa_com_unidade("Informe a taxa (ex: 20% a.a.): ", &unidade_taxa);
    UnidadeTempo unidade_resposta;
    double periodos_na_taxa;
    double tempo_resposta;

    if (taxa == 0.0) {
        printf("Para calcular tempo, a taxa nao pode ser 0.\n\n");
        return;
    }

    if (1.0 + taxa <= 0.0 || valor_futuro / valor_presente <= 0.0) {
        printf("Nao foi possivel calcular o logaritmo com os dados informados.\n\n");
        return;
    }

    unidade_resposta = ler_unidade_tempo("Unidade desejada para o tempo:");
    periodos_na_taxa = calcular_tempo(valor_presente, valor_futuro, taxa);
    tempo_resposta = converter_tempo(periodos_na_taxa, unidade_taxa, unidade_resposta);

    printf("\n===== Resultado =====\n");
    printf("Tempo encontrado: %.6f %s\n", tempo_resposta, nome_unidade_plural(unidade_resposta));
    printf("=====================\n\n");
}

static void submenu_juros_compostos(void) {
    int opcao;

    do {
        printf("===== Juros Compostos =====\n");
        printf("1 - Calcular Valor Presente / Capital (VP)\n");
        printf("2 - Calcular Valor Futuro / Montante (VF)\n");
        printf("3 - Calcular Juros (J)\n");
        printf("4 - Calcular Taxa (i)\n");
        printf("5 - Calcular Tempo (n)\n");
        printf("0 - Voltar\n");

        opcao = ler_opcao_menu("Escolha uma opcao: ", 0, 5);

        switch (opcao) {
            case 1:
                calcular_vp_menu();
                break;
            case 2:
                calcular_vf_menu();
                break;
            case 3:
                calcular_juros_menu();
                break;
            case 4:
                calcular_taxa_menu();
                break;
            case 5:
                calcular_tempo_menu();
                break;
            case 0:
                break;
        }
    } while (opcao != 0);
}

static void menu_taxas_equivalentes(void) {
    UnidadeTempo unidade_origem;
    double taxa_origem = ler_taxa_com_unidade("Informe a taxa efetiva (ex: 10% a.s.): ",
                                              &unidade_origem);
    UnidadeTempo unidade_destino = ler_unidade_tempo("Unidade desejada para a taxa:");
    double taxa_destino = converter_taxa_equivalente(taxa_origem,
                                                     dias_por_unidade(unidade_origem),
                                                     dias_por_unidade(unidade_destino));

    printf("\n===== Resultado =====\n");
    printf("Taxa equivalente: %.6f%% %s\n", taxa_destino * 100.0, nome_taxa(unidade_destino));
    printf("=====================\n\n");
}

static void menu_nominal_efetiva(void) {
    int opcao;
    double taxa;
    double capitalizacoes;
    double resultado;
    UnidadeTempo unidade_taxa;
    UnidadeTempo periodo;

    printf("===== Taxa Nominal e Efetiva Proporcional =====\n");
    printf("1 - Taxa nominal para taxa efetiva proporcional\n");
    printf("2 - Taxa efetiva proporcional para taxa nominal\n");
    printf("0 - Voltar\n");

    opcao = ler_opcao_menu("Escolha uma opcao: ", 0, 2);
    if (opcao == 0) {
        return;
    }

    if (opcao == 1) {
        taxa = ler_taxa_com_unidade("Informe a taxa nominal (ex: 24% a.a.): ", &unidade_taxa);
        periodo = ler_periodo("Informe o periodo de capitalizacao (por dia, mensal, bimestral, trimestral, semestral ou anual): ");
        capitalizacoes = dias_por_unidade(unidade_taxa) / dias_por_unidade(periodo);

        if (capitalizacoes < 1.0) {
            printf("O periodo de capitalizacao deve caber dentro do periodo da taxa nominal.\n\n");
            return;
        }

        resultado = taxa_nominal_para_efetiva(taxa, capitalizacoes);
        printf("\n===== Resultado =====\n");
        printf("Taxa nominal informada: %.6f%% %s\n", taxa * 100.0, nome_taxa(unidade_taxa));
        printf("Periodo de capitalizacao: %s\n", nome_unidade(periodo));
        printf("Capitalizacoes no periodo nominal (k): %.6f\n", capitalizacoes);
        printf("Taxa efetiva proporcional: %.6f%% %s\n", resultado * 100.0, nome_taxa(periodo));
    } else {
        taxa = ler_taxa_com_unidade("Informe a taxa efetiva proporcional (ex: 2% a.m.): ",
                                    &unidade_taxa);
        periodo = ler_periodo("Informe o periodo nominal desejado (por dia, mensal, bimestral, trimestral, semestral ou anual): ");
        capitalizacoes = dias_por_unidade(periodo) / dias_por_unidade(unidade_taxa);

        if (capitalizacoes < 1.0) {
            printf("O periodo nominal deve conter pelo menos uma capitalizacao.\n\n");
            return;
        }

        resultado = taxa_efetiva_para_nominal(taxa, capitalizacoes);
        printf("\n===== Resultado =====\n");
        printf("Taxa efetiva informada: %.6f%% %s\n", taxa * 100.0, nome_taxa(unidade_taxa));
        printf("Periodo nominal desejado: %s\n", nome_unidade(periodo));
        printf("Capitalizacoes no periodo nominal (k): %.6f\n", capitalizacoes);
        printf("Taxa nominal: %.6f%% %s\n", resultado * 100.0, nome_taxa(periodo));
    }
    printf("=====================\n\n");
}

static void menu_conversao_tempo(void) {
    UnidadeTempo origem;
    double tempo = ler_tempo_com_unidade("Informe o tempo de origem (ex: 2 anos): ", &origem);
    UnidadeTempo destino = ler_unidade_tempo("Unidade de destino:");
    double convertido = converter_tempo(tempo, origem, destino);

    printf("\n===== Resultado =====\n");
    printf("%.6f %s = %.6f %s\n", tempo, nome_unidade_plural(origem),
           convertido, nome_unidade_plural(destino));
    printf("=====================\n\n");
}

int main(void) {
    int opcao;

    do {
        printf("===== Calculadora Financeira =====\n");
        printf("1 - Juros compostos\n");
        printf("2 - Conversao de taxas equivalentes\n");
        printf("3 - Taxa nominal e taxa efetiva proporcional\n");
        printf("4 - Conversao simples de tempo\n");
        printf("0 - Sair\n");

        opcao = ler_opcao_menu("Escolha uma opcao: ", 0, 4);

        switch (opcao) {
            case 1:
                submenu_juros_compostos();
                break;
            case 2:
                menu_taxas_equivalentes();
                break;
            case 3:
                menu_nominal_efetiva();
                break;
            case 4:
                menu_conversao_tempo();
                break;
            case 0:
                printf("Encerrando a calculadora.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
