#include <stdio.h>

#include "entrada.h"
#include "unidades.h"

double dias_por_unidade(UnidadeTempo unidade) {
    switch (unidade) {
        case UNIDADE_DIA:
            return DIAS_POR_DIA;
        case UNIDADE_MES:
            return DIAS_POR_MES;
        case UNIDADE_ANO:
            return DIAS_POR_ANO;
        case UNIDADE_SEMESTRE:
            return DIAS_POR_SEMESTRE;
        case UNIDADE_BIMESTRE:
            return DIAS_POR_BIMESTRE;
        case UNIDADE_TRIMESTRE:
            return DIAS_POR_TRIMESTRE;
        default:
            return DIAS_POR_DIA;
    }
}

double converter_tempo(double valor, UnidadeTempo origem, UnidadeTempo destino) {
    double valor_em_dias = valor * dias_por_unidade(origem);
    return valor_em_dias / dias_por_unidade(destino);
}

double calcular_periodos(double tempo, UnidadeTempo unidade_tempo, UnidadeTempo unidade_taxa) {
    return converter_tempo(tempo, unidade_tempo, unidade_taxa);
}

UnidadeTempo ler_unidade_tempo(const char *mensagem) {
    int opcao;

    printf("%s\n", mensagem);
    printf("1 - dia\n");
    printf("2 - mes\n");
    printf("3 - ano\n");
    printf("4 - semestre\n");
    printf("5 - bimestre\n");
    printf("6 - trimestre\n");

    do {
        opcao = ler_opcao_menu("Escolha uma unidade: ", 0, 6);
        if (opcao == 0) {
            printf("Opcao 0 nao e valida para unidade. Tente novamente.\n");
        }
    } while (opcao == 0);

    return (UnidadeTempo)opcao;
}

const char *nome_unidade(UnidadeTempo unidade) {
    switch (unidade) {
        case UNIDADE_DIA:
            return "dia";
        case UNIDADE_MES:
            return "mes";
        case UNIDADE_ANO:
            return "ano";
        case UNIDADE_SEMESTRE:
            return "semestre";
        case UNIDADE_BIMESTRE:
            return "bimestre";
        case UNIDADE_TRIMESTRE:
            return "trimestre";
        default:
            return "unidade";
    }
}

const char *nome_unidade_plural(UnidadeTempo unidade) {
    switch (unidade) {
        case UNIDADE_DIA:
            return "dias";
        case UNIDADE_MES:
            return "meses";
        case UNIDADE_ANO:
            return "anos";
        case UNIDADE_SEMESTRE:
            return "semestres";
        case UNIDADE_BIMESTRE:
            return "bimestres";
        case UNIDADE_TRIMESTRE:
            return "trimestres";
        default:
            return "unidades";
    }
}

const char *nome_taxa(UnidadeTempo unidade) {
    switch (unidade) {
        case UNIDADE_DIA:
            return "a.d.";
        case UNIDADE_MES:
            return "a.m.";
        case UNIDADE_ANO:
            return "a.a.";
        case UNIDADE_SEMESTRE:
            return "a.s.";
        case UNIDADE_BIMESTRE:
            return "a.b.";
        case UNIDADE_TRIMESTRE:
            return "a.t.";
        default:
            return "por periodo";
    }
}
