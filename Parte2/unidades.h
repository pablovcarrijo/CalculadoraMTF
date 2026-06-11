#ifndef UNIDADES_H
#define UNIDADES_H

typedef enum {
    UNIDADE_DIA = 1,
    UNIDADE_MES = 2,
    UNIDADE_ANO = 3,
    UNIDADE_SEMESTRE = 4,
    UNIDADE_BIMESTRE = 5,
    UNIDADE_TRIMESTRE = 6
} UnidadeTempo;

#define DIAS_POR_DIA 1.0
#define DIAS_POR_MES 30.0
#define DIAS_POR_ANO 360.0
#define DIAS_POR_SEMESTRE 180.0
#define DIAS_POR_BIMESTRE 60.0
#define DIAS_POR_TRIMESTRE 90.0

double dias_por_unidade(UnidadeTempo unidade);
double converter_tempo(double valor, UnidadeTempo origem, UnidadeTempo destino);
double calcular_periodos(double tempo, UnidadeTempo unidade_tempo, UnidadeTempo unidade_taxa);
UnidadeTempo ler_unidade_tempo(const char *mensagem);
const char *nome_unidade(UnidadeTempo unidade);
const char *nome_unidade_plural(UnidadeTempo unidade);
const char *nome_taxa(UnidadeTempo unidade);

#endif
