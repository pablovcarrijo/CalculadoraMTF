#include <math.h>

#include "financeira.h"

double calcular_valor_futuro(double valor_presente, double taxa, double periodos) {
    return valor_presente * pow(1.0 + taxa, periodos);
}

double calcular_valor_presente(double valor_futuro, double taxa, double periodos) {
    return valor_futuro / pow(1.0 + taxa, periodos);
}

double calcular_juros(double valor_presente, double valor_futuro) {
    return valor_futuro - valor_presente;
}

double calcular_taxa(double valor_presente, double valor_futuro, double periodos) {
    return pow(valor_futuro / valor_presente, 1.0 / periodos) - 1.0;
}

double calcular_tempo(double valor_presente, double valor_futuro, double taxa) {
    return log(valor_futuro / valor_presente) / log(1.0 + taxa);
}

double taxa_nominal_para_efetiva(double taxa_nominal, double capitalizacoes) {
    return taxa_nominal / capitalizacoes;
}

double taxa_efetiva_para_nominal(double taxa_efetiva, double capitalizacoes) {
    return taxa_efetiva * capitalizacoes;
}

double converter_taxa_equivalente(double taxa_origem, double dias_origem, double dias_destino) {
    return pow(1.0 + taxa_origem, dias_destino / dias_origem) - 1.0;
}
