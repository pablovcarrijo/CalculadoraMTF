# Calculadora Financeira em C

Projeto em C puro para calculos de capitalizacao composta, conversao de taxas equivalentes, taxa nominal, taxa efetiva proporcional e conversao simples de tempo.

## Como compilar

```bash
gcc -Wall -Wextra -std=c11 main.c financeira.c unidades.c entrada.c -o calculadora -lm
```

## Como executar

```bash
./calculadora
```

No Windows, se o executavel for gerado com extensao `.exe`:

```bash
./calculadora.exe
```

## Formulas usadas

- Valor futuro: `VF = VP * pow(1 + i, n)`
- Valor presente: `VP = VF / pow(1 + i, n)`
- Juros: `J = VF - VP`
- Juros a partir do capital: `J = VP * (pow(1 + i, n) - 1)`
- Taxa: `i = pow(VF / VP, 1.0 / n) - 1`
- Tempo: `n = log(VF / VP) / log(1 + i)`
- Taxa equivalente: `i_destino = pow(1 + i_origem, dias_destino / dias_origem) - 1`
- Taxa nominal para efetiva proporcional: `i_efetiva = i_nominal / k`
- Taxa efetiva proporcional para nominal: `i_nominal = i_efetiva * k`

A taxa digitada pelo usuario deve estar em porcentagem e com a unidade na mesma entrada.

Exemplos:

- `5% a.d.` para 5% ao dia
- `5% a.m.` para 5% ao mes
- `5% a.b.` para 5% ao bimestre
- `5% a.t.` para 5% ao trimestre
- `5% a.a.` para 5% ao ano
- `5% a.s.` para 5% ao semestre

Internamente, o programa converte a taxa para decimal. Por exemplo, `5% a.m.` vira `0.05`.

O tempo tambem deve ser digitado com valor e unidade na mesma entrada.

Exemplos:

- `30 dias`
- `5 meses`
- `1 bimestre`
- `1 trimestre`
- `2 anos`
- `1 semestre`

## Convencao 30/360

O projeto usa a convencao financeira:

- 1 dia = 1 dia
- 1 mes = 30 dias
- 1 bimestre = 60 dias
- 1 trimestre = 90 dias
- 1 semestre = 180 dias
- 1 ano = 360 dias

Esses valores ficam definidos em `unidades.h`, facilitando alteracoes futuras.

## Exemplos de uso

### Exemplo 1: calcular VF

Dados:

- VP = 400
- taxa = 5% a.m.
- tempo = 3 meses

Resultado aproximado:

- VF = R$ 463.05
- J = R$ 63.05

### Exemplo 2: calcular VP

Dados:

- VF = 800
- taxa = 8% a.m.
- tempo = 4 meses

Resultado aproximado:

- VP = R$ 588.02

### Exemplo 3: taxa equivalente

Converter `10% a.s.` para taxa anual:

- resultado = `21% a.a.`

### Exemplo 4: taxa nominal para efetiva

Taxa nominal de 24% ao ano com capitalizacao mensal:

- o programa calcula k automaticamente: `360 / 30 = 12`
- resultado = 2% a.m.

### Exemplo 5: calcular tempo

Dados:

- VP = 1000
- VF = 2000
- taxa = 20% a.a.

Resultado aproximado:

- tempo = 3.801784 anos

## Organizacao dos arquivos

- `main.c`: menus, chamadas das funcoes e exibicao dos resultados.
- `financeira.h`: declaracoes das funcoes financeiras.
- `financeira.c`: implementacao das formulas financeiras.
- `unidades.h`: enum de unidades e constantes de conversao.
- `unidades.c`: conversao de tempo, periodos e nomes das unidades.
- `entrada.h`: declaracoes das funcoes auxiliares de leitura.
- `entrada.c`: leitura segura de inteiros, doubles e opcoes de menu.
