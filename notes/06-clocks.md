
# Clocks do STM32

## Objetivo

Apresentar os principais conceitos relacionados ao sistema de gerenciamento de clock nos microcontroladores STM32, incluindo a hierarquia de osciladores (internos e externos), a configuração do periférico **RCC** e o impacto das frequências no desempenho e consumo de energia.

---

# Sumário

- [Introdução](#introdução)
- [Sistema RCC](#sistema-rcc)
- [Fontes de Clock](#fontes-de-clock)
- [Osciladores Internos](#osciladores-internos)
- [Osciladores Externos](#osciladores-externos)
- [Clock Tree (Árvore de Clock)](#clock-tree)
- [PLL (Phase Locked Loop)](#pll---phase-locked-loop)
- [Clock dos Periféricos](#clock-dos-periféricos)
- [Segurança: Clock Security System (CSS)](#clock-security-system-css)
- [Impacto no Consumo e Performance](#impacto-no-consumo-e-performance)
- [Referências](#referências)

---

# Introdução

O sistema de clock é o "coração" do microcontrolador, coordenando a execução de instruções e o funcionamento dos periféricos. Diferente de sistemas simples, o STM32 possui múltiplas fontes de clock que podem ser combinadas para otimizar o compromisso entre **alta performance** e **baixo consumo de energia**.

# Sistema RCC

O periférico **RCC (Reset and Clock Control)** é o responsável por gerenciar a ativação das fontes de clock, a configuração dos barramentos (AHB/APB) e o controle de reset do sistema.
*   **Gating de Clock:** Para economizar energia, o clock de quase todos os periféricos é mantido desligado por padrão e deve ser habilitado via software através dos registradores `RCC_AHBxENR` ou `RCC_APBxENR`.

# Fontes de Clock

O sistema divide as fontes em dois grandes grupos baseados na velocidade:

1.  **High Speed (Alta Velocidade):** Utilizados para o processador (SYSCLK) e periféricos de alta taxa de dados. Exemplos: HSI16, HSE, PLL, MSI (na série L4).
2.  **Low Speed (Baixa Velocidade):** Utilizados principalmente para o RTC (Real-Time Clock) e o Independent Watchdog (IWDG). Exemplos: LSI, LSE.

# Osciladores Internos

São integrados ao chip, reduzindo custo e espaço na placa:
*   **HSI16 (High Speed Internal):** RC interno de **16 MHz**. É a fonte padrão após o reset.
*   **MSI (Multispeed Internal - exclusivo L4):** Oscilador flexível que gera 12 frequências (100 kHz a 48 MHz). Pode ser calibrado pelo LSE para atingir alta precisão, permitindo o uso de USB sem cristal externo.
*   **LSI (Low Speed Internal):** RC interno de aproximadamente **32 kHz**. Baixo consumo, mas baixa precisão. Ideal para o IWDG.
*   **HSI48:** RC interno de **48 MHz** dedicado a periféricos que exigem essa frequência fixa, como USB e RNG.

# Osciladores Externos

Exigem componentes na placa (como cristais de quartzo), oferecendo maior precisão:
*   **HSE (High Speed External):** Suporta cristais de **4 a 48 MHz**. Pode operar em modo *Bypass* (sinal de clock externo injetado) ou *Xtal* (ressonador/cristal).
*   **LSE (Low Speed External):** Cristal de **32.768 kHz**. Essencial para aplicações de relógio de tempo real (RTC) devido à sua alta estabilidade.

# Clock Tree

A árvore de clock distribui o sinal da fonte escolhida para todo o chip através de divisores (prescalers) e multiplicadores.
*   **SYSCLK (System Clock):** É o clock principal do sistema (máx. **170 MHz** no G4 e **80 MHz** no L4).
*   **HCLK (AHB Clock):** Derivado do SYSCLK, alimenta o núcleo Cortex-M4, memórias Flash/SRAM e o DMA.
*   **PCLK1 / PCLK2 (APB Clocks):** Alimentam os periféricos nos barramentos APB1 e APB2.

# PLL - Phase Locked Loop

O **PLL** é um multiplicador de frequência que recebe sinais do HSI16, HSE ou MSI e os eleva para as frequências máximas de operação do chip. No STM32G4, ele possui saídas independentes:
*   **PLL "R":** Para o clock do sistema (SYSCLK).
*   **PLL "Q":** Para USB, RNG e interfaces de áudio (48 MHz).
*   **PLL "P":** Para interfaces analógicas (ADC).

# Clock dos Periféricos

Alguns periféricos possuem **Kernel Clocks** independentes, o que permite mudar a frequência do processador (SYSCLK) sem alterar a taxa de baud rate de uma UART ou a velocidade de amostragem de um ADC.
*   Exemplo: Uma UART pode continuar operando via HSI16 ou LSE mesmo que o sistema mude para uma frequência menor para economizar energia.

# Clock Security System (CSS)

É um mecanismo de hardware que monitora o oscilador externo (HSE). Caso o cristal falhe (ex: quebra física), o CSS detecta a falha, gera uma interrupção de emergência (NMI) e comuta automaticamente o clock do sistema para o oscilador interno (HSI16) para evitar o travamento do código.

# Impacto no Consumo e Performance

A frequência de operação dita o consumo dinâmico de corrente ($I \propto f \cdot V^2$). No STM32G4:
*   **Range 1 (Boost Mode):** Permite até **170 MHz** para máxima performance.
*   **Range 2 (Low Power):** Limita a frequência a **26 MHz** para reduzir drasticamente o consumo.
*   Em modos como **Stop** e **Standby**, os osciladores de alta velocidade são desligados, restando apenas LSI ou LSE para manter o RTC ou Watchdogs ativos.

# Referências
- **RM0440:** Manual de Referência - STM32G4.
- **DS12288:** Datasheet - STM32G474.
- **AN2867:** Guia de design de osciladores para STM32.

---

**Dica Prática:** No **STM32CubeMX**, a aba *Clock Configuration* permite visualizar graficamente toda a árvore de clock e as interdependências entre as fontes e os barramentos, facilitando o ajuste de multiplicadores para atingir a frequência desejada sem violar os limites do hardware.