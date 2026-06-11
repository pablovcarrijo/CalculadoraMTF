#ifndef ENTRADA_H
#define ENTRADA_H

int ler_int(const char *mensagem);
int ler_texto(const char *mensagem, char *buffer, int tamanho);
double ler_double_maior_que(const char *mensagem, double minimo);
double ler_double_positivo(const char *mensagem);
int ler_opcao_menu(const char *mensagem, int minimo, int maximo);

#endif
