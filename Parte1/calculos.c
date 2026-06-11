#include "calculos.h"

double calcularJuros(double vp, double i, double n)
{
    return vp * i * n;
}

double calcularMontante(double vp, double i, double n)
{
    return vp * (1.0 + i * n);
}

double calcularValorPresente(double vf, double i, double n)
{
    return vf / (1.0 + i * n);
}

double calcularTaxa(double j, double vp, double n)
{
    return j / (vp * n);
}

double calcularTempo(double j, double vp, double i)
{
    return j / (vp * i);
}

double calcularTaxaEfetiva(double ic, double n)
{
    return ic / (1.0 - ic * n);
}

double calcularTaxaComercial(double i, double n)
{
    return i / (1.0 + i * n);
}
