#ifndef FINANCEIRA_H
#define FINANCEIRA_H

double calcular_valor_futuro(double valor_presente, double taxa, double periodos);
double calcular_valor_presente(double valor_futuro, double taxa, double periodos);
double calcular_juros(double valor_presente, double valor_futuro);
double calcular_taxa(double valor_presente, double valor_futuro, double periodos);
double calcular_tempo(double valor_presente, double valor_futuro, double taxa);
double taxa_nominal_para_efetiva(double taxa_nominal, double capitalizacoes);
double taxa_efetiva_para_nominal(double taxa_efetiva, double capitalizacoes);
double converter_taxa_equivalente(double taxa_origem, double dias_origem, double dias_destino);

#endif
