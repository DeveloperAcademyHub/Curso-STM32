
# DAC (Conversor Digital-Analógico)

## Objetivo

Apresentar os conceitos fundamentais do DAC (*Digital-to-Analog Converter*) presente em microcontroladores STM32, como os das placas **NUCLEO-G474RE** e **NUCLEO-L476RG**, abordando suas características técnicas, modos de operação e integração com DMA.

---

# Sumário

- [Introdução](#introdução)
- [Funcionamento Básico](#funcionamento-básico)
- [Resolução](#resolução)
- [Faixa de Saída](#faixa-de-saída)
- [Configuração no STM32CubeMX](#configuração-no-stm32cubemx)
- [Inicialização via HAL](#inicialização-via-hal)
- [Geração de Formas de Onda](#geração-de-formas-de-onda)
- [DAC com DMA](#dac-com-dma)

---

# Introdução

O periférico DAC é um conversor de 12 bits que transforma valores digitais em sinais de tensão analógica. 
*   **STM32L476RG:** Possui **dois canais** de saída DAC de 12 bits.
*   **STM32G474RE:** Oferece uma configuração mais robusta com até **sete canais** de 12 bits: 3 canais externos com buffer (1 MSPS) e 4 canais internos sem buffer (15 MSPS) voltados para periféricos internos como comparadores e amplificadores operacionais.

# Funcionamento Básico

O DAC utiliza uma estrutura de **cadeias de resistores integrados** e um amplificador configurado como inversor. 
O processo de conversão ocorre em etapas:
1.  O dado é escrito pelo software em um Registrador de Retenção de Dados (**DHR**).
2.  O dado é transferido automaticamente (ou por trigger) para o Registrador de Saída de Dados (**DOR**).
3.  O valor em DOR é convertido na tensão analógica final disponível no pino de saída.
4.  Opcionalmente, um **buffer de saída** pode ser habilitado para reduzir a impedância e permitir acionar cargas externas diretamente sem necessidade de um OpAmp externo.

# Resolução

A resolução nativa do DAC é de **12 bits**, mas ele pode ser configurado para operar em **8 bits**. 
*   No modo de 12 bits, os dados podem ser alinhados à **esquerda** ou à **direita** nos registradores de 16 bits.
*   No modo de 8 bits, o alinhamento é sempre à direita.

# Faixa de Saída

A conversão linear ocorre entre **0 e $V_{REF+}$**. A tensão de saída é calculada pela fórmula:
$$\text{V}_{OUT} = V_{REF+} \times \frac{DOR}{4096}$$
Onde $V_{REF+}$ é a tensão de referência positiva conectada ao chip.

# Configuração no STM32CubeMX

Para configurar o DAC no STM32CubeMX:
1.  **Habilitar o Periférico:** Selecionar o DAC e ativar os canais desejados (ex: *OUT1 Configuration* no pino **PA4** ou *OUT2* no **PA5**).
2.  **Referência de Tensão:** Definir se $V_{REF+}$ virá de um pino externo ou do buffer de referência de tensão interno (**VREFBUF**). O VREFBUF pode fornecer tensões fixas como 2.048 V, 2.5 V ou 2.9 V (na série G4).
3.  **Output Buffer:** Decidir se o buffer de saída será ativado (recomendado para acionar cargas) ou desativado (para menor consumo ou conexões apenas internas).

# Inicialização via HAL

O uso do DAC via biblioteca HAL segue um fluxo padrão:
1.  Habilitar o clock do barramento APB para o DAC via `HAL_DAC_Init()`.
2.  Configurar o pino GPIO correspondente em **modo analógico**.
3.  Configurar o canal (trigger, buffer, etc.) usando `HAL_DAC_ConfigChannel()`.
4.  Iniciar o periférico com `HAL_DAC_Start()` para conversão simples ou `HAL_DAC_Start_DMA()` para transferências automáticas.

# Geração de Formas de Onda

O hardware do DAC pode gerar formas de onda automaticamente, sem intervenção constante da CPU, quando um gatilho (trigger) de timer é utilizado:
*   **Ruído (Noise):** Baseado em um registrador de deslocamento de feedback linear (LFSR).
*   **Onda Triangular:** Gerada por um contador interno que incrementa e decrementa até uma amplitude definida.
*   **Onda Dente de Serra (Sawtooth):** Recurso avançado disponível na série **STM32G4**, permitindo configurar valores de incremento e reset via hardware.

# DAC com DMA

O uso de DMA (*Direct Memory Access*) é ideal para gerar sinais complexos (como senoides) a partir de tabelas na memória:
*   **Funcionamento:** Cada vez que um gatilho externo (geralmente um timer) ocorre, o DMA transfere o próximo valor da memória diretamente para o registrador DHR do DAC.
*   **Double Data Mode:** Na série G4, o DAC suporta um modo de dado duplo que permite transferir dois valores de 12 bits em uma única transação de 32 bits, reduzindo a atividade no barramento AHB.
*   **Segurança:** O sistema monitora erros de **DMA Underrun**, que ocorrem se um novo trigger de conversão chegar antes que o DMA tenha terminado de carregar o dado anterior.