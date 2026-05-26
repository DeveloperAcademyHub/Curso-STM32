# Revisão de Linguagem C

## Objetivo

Revisar os principais conceitos da linguagem C utilizados no desenvolvimento de sistemas embarcados com microcontroladores STM32.

---

# Sumário

- [Introdução](#introdução)
- [Estrutura Básica de um Programa em C](#estrutura-básica-de-um-programa-em-c)
- [Tipos de Dados](#tipos-de-dados)
- [Variáveis e Constantes](#variáveis-e-constantes)
- [Operadores](#operadores)
- [Estruturas Condicionais](#estruturas-condicionais)
- [Estruturas de Repetição](#estruturas-de-repetição)
- [Funções](#funções)
- [Ponteiros](#ponteiros)
- [Arrays e Strings](#arrays-e-strings)
- [Structs](#structs)
- [Manipulação de Bits](#manipulação-de-bits)
- [Conversão Numérica](#conversão-numérica)
- [Boas Práticas](#boas-práticas)
- [Referências](#referências)

---

# Introdução

A linguagem C é a principal linguagem utilizada no desenvolvimento de sistemas embarcados devido à sua:

- alta eficiência;
- baixo overhead;
- acesso direto ao hardware;
- portabilidade;
- desempenho.

Grande parte das bibliotecas HAL e LL da STMicroelectronics são desenvolvidas em C.

---

# Estrutura Básica de um Programa em C

Exemplo simples:

```c
#include <stdio.h>

int main(void)
{
    printf("Hello World\n");

    while(1)
    {

    }
}
```

---

## Componentes Principais

| Elemento | Função |
|---|---|
| `#include` | Inclusão de bibliotecas |
| `main()` | Função principal |
| `while(1)` | Loop infinito |
| `;` | Finalização de instrução |

> **Nota:** Em sistemas embarcados é comum utilizar loops infinitos para execução contínua do firmware.

---

# Tipos de Dados

Os tipos de dados definem o espaço de memória e o tipo de informação armazenada.

---

## Inteiros

| Tipo | Tamanho típico |
|---|---|
| `char` | 8 bits |
| `short` | 16 bits |
| `int` | 32 bits |
| `long` | 32 ou 64 bits |

---

## Tipos sem sinal

```c
uint8_t
uint16_t
uint32_t
uint64_t
```

Esses tipos são muito utilizados em sistemas embarcados.

---

## Tipos com sinal

```c
int8_t
int16_t
int32_t
int64_t
```

---

## Ponto flutuante

| Tipo | Precisão |
|---|---|
| `float` | Simples precisão |
| `double` | Dupla precisão |

> **Importante:** Operações com ponto flutuante podem aumentar o consumo de processamento em microcontroladores.

---

# Variáveis e Constantes

---

## Variáveis

```c
int valor = 10;
float tensao = 3.3;
```

---

## Constantes

```c
#define PI 3.14159

const int ledPin = 13;
```

---

# Operadores

---

## Operadores Aritméticos

| Operador | Função |
|---|---|
| `+` | Soma |
| `-` | Subtração |
| `*` | Multiplicação |
| `/` | Divisão |
| `%` | Resto |

---

## Operadores Relacionais

| Operador | Função |
|---|---|
| `==` | Igual |
| `!=` | Diferente |
| `>` | Maior |
| `<` | Menor |
| `>=` | Maior igual |
| `<=` | Menor igual |

---

## Operadores Lógicos

| Operador | Função |
|---|---|
| `&&` | AND |
| `\|\|` | OR |
| `!` | NOT |

---

# Estruturas Condicionais

---

## if / else

```c
if(valor > 10)
{
    led = 1;
}
else
{
    led = 0;
}
```

---

## switch

```c
switch(opcao)
{
    case 0:
        break;

    case 1:
        break;

    default:
        break;
}
```

---

# Estruturas de Repetição

---

## while

```c
while(1)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
```

---

## for

```c
for(int i = 0; i < 10; i++)
{

}
```

---

## do while

```c
do
{

} while(condicao);
```

---

# Funções

Funções permitem modularizar o código.

---

## Exemplo

```c
int soma(int a, int b)
{
    return a + b;
}
```

---

## Protótipos

```c
void piscarLed(void);
```

---

# Ponteiros

Ponteiros armazenam endereços de memória.

---

## Declaração

```c
int valor = 10;
int *ptr = &valor;
```

---

## Operadores

| Operador | Função |
|---|---|
| `&` | Endereço |
| `*` | Conteúdo |

---

## Aplicação em Sistemas Embarcados

- acesso a registradores;
- manipulação de memória;
- buffers DMA;
- periféricos.

---

# Arrays e Strings

---

## Arrays

```c
int vetor[10];
```

---

## Strings

```c
char texto[] = "STM32";
```

---

# Structs

Structs agrupam diferentes tipos de dados.

---

## Exemplo

```c
typedef struct
{
    uint16_t adc;
    float temperatura;
} Sensor_t;
```

---

# Manipulação de Bits

Manipulação de bits é extremamente importante em sistemas embarcados.

---

## Operações Bitwise

| Operador | Função |
|---|---|
| `&` | AND |
| `\|` | OR |
| `^` | XOR |
| `~` | NOT |
| `<<` | Shift esquerda |
| `>>` | Shift direita |

---

## Exemplo

```c
GPIOA->ODR |= (1 << 5);
```

---

## Máscaras de Bits

```c
uint8_t flag = 0x00;

flag |= (1 << 0);
flag &= ~(1 << 0);
```

---

# Conversão Numérica

---

## Decimal

Base 10.

```c
int valor = 25;
```

---

## Hexadecimal

Base 16.

```c
int valor = 0x1A;
```

---

## Binário

Base 2.

```c
int valor = 0b1010;
```

---

## ASCII

Tabela utilizada para representação de caracteres.

| Caractere | Decimal | Hexadecimal |
|---|---|---|
| A | 65 | 0x41 |
| a | 97 | 0x61 |
| 0 | 48 | 0x30 |

---

# Boas Práticas

---

## Nomes descritivos

```c
uint16_t adcValue;
```

Evite:

```c
uint16_t x;
```

---

## Modularização

Separe o código em:

- funções;
- arquivos `.c`;
- arquivos `.h`.

---

## Comentários

```c
// Inicializa ADC
HAL_ADC_Start(&hadc1);
```

---

## Evite números mágicos

Prefira:

```c
#define ADC_MAX 4095
```

Ao invés de:

```c
valor = valor / 4095;
```

---

# Ferramentas Auxiliares

---

## Compiladores e IDEs

- Dev-C++;
- STM32CubeIDE;
- VSCode.

---

## Ferramentas Online

- https://cplusplus.com/
- https://www.calculadoraonline.com.br/conversao-bases
- https://www.ibm.com/docs/pt-br/aix/7.3?topic=adapters-ascii-decimal-hexadecimal-octal-binary-conversion-table

---

# Observações

> **Importante:** Ponteiros e manipulação de bits são conceitos fundamentais no desenvolvimento embarcado.

> **Nota:** O uso excessivo de `float` pode impactar desempenho e consumo de memória.

> **Nota:** Tipos fixos como `uint32_t` são preferíveis em sistemas embarcados por garantirem tamanho conhecido.

---

# Referências

- https://cplusplus.com/
- https://embarcados.com.br/linguagem-c-guia-completo/
- https://www.each.usp.br/digiampietri/ACH2023/tabelasemc.html
- https://www.ibm.com/docs/pt-br/aix/7.3?topic=adapters-ascii-decimal-hexadecimal-octal-binary-conversion-table
- https://www.calculadoraonline.com.br/conversao-bases