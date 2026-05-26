# Timers do STM32

## Objetivo

Apresentar os conceitos fundamentais dos timers nos microcontroladores STM32, abrangendo desde a base de tempo simples até funções avançadas como **PWM de alta resolução**, interrupções e sincronização de periféricos, com foco nas placas **NUCLEO-G474RE** (Série G4) e **NUCLEO-L476RG** (Série L4).

---

# Sumário

- [Introdução](#introdução)
- [Tipos de Timers STM32](#tipos-de-timers-stm32)
- [Clock dos Timers](#clock-dos-timers)
- [Estrutura Básica](#estrutura-básica)
- [Prescaler e ARR](#prescaler-e-arr)
- [Base de Tempo](#base-de-tempo)
- [Recursos Avançados: HRTIM](#recursos-avançados-hrtim)
- [Interrupções com Timer](#interrupções-com-timer)
- [Observações](#observações)
- [Referências](#referências)

---

# Introdução

Os timers são periféricos fundamentais que realizam operações de contagem de eventos e gerenciamento de tempo de forma **independente da CPU**. Essa autonomia permite que o processador execute outras tarefas enquanto o timer gera sinais periódicos, mede frequências ou controla a potência de cargas via PWM.

**Principais funções:**
- **Geração de delays precisos** sem bloqueio do código;
- **Interrupções periódicas** para tarefas de tempo real;
- **Modulação por Largura de Pulso (PWM)** para controle de motores e LEDs;
- **Captura de Sinais (Input Capture)** para medir frequência e largura de pulso;
- **Sincronização entre periféricos** (ex: disparar um ADC exatamente no pico de um sinal PWM).

---

# Tipos de Timers STM32

O microcontrolador STM32G474RE, por exemplo, possui até **17 timers** divididos em categorias conforme sua complexidade:

| Categoria | Instâncias (Ex: G474) | Resolução | Principais Recursos |
| :--- | :--- | :--- | :--- |
| **Alta Resolução (HRTIM)** | HRTIM1 | 16-bit | **184 ps de resolução**, 12 canais PWM, ideal para fontes chaveadas. |
| **Controle Avançado** | TIM1, TIM8, TIM20 | 16-bit | PWM complementar com **Dead-time**, parada de emergência (Break). |
| **Uso Geral (32-bit)** | TIM2, TIM5 | 32-bit | Contagem estendida, suporte a **Quadrature Encoder**. |
| **Uso Geral (16-bit)** | TIM3, TIM4, TIM15-17 | 16-bit | PWM, Input Capture, Output Compare. |
| **Básicos** | TIM6, TIM7 | 16-bit | Utilizados principalmente como base de tempo e trigger para **DAC**. |
| **Baixo Consumo** | LPTIM1 | 16-bit | Funciona em modos de baixo consumo (**Stop mode**) via LSI/LSE. |

---

# Clock dos Timers

A frequência fornecida ao timer (`tim_ker_ck`) depende da configuração do barramento APB. No STM32G4:
1. Se o prescaler do APB for **1**, a frequência do timer será igual à do barramento.
2. Se o prescaler do APB for **diferente de 1**, a frequência do timer será o **dobro (x2)** da frequência do barramento APB correspondente.

As fontes de clock podem ser internas (**HSI16, LSI**) ou externas (**HSE, LSE**). O timer de alta resolução (**HRTIM**), especificamente, opera em um domínio de clock de até **170 MHz**.

---

# Estrutura Básica

Um timer STM32 é composto por três blocos principais que definem seu comportamento:

### 1. Prescaler (PSC)
O **Prescaler** divide o clock de entrada para reduzir a velocidade da contagem. É um registrador de 16 bits que pode dividir o clock por qualquer valor entre **1 e 65536**.
- *Fórmula do clock do contador:* $f_{CNT} = \frac{f_{TIM\_CLK}}{PSC + 1}$

### 2. Auto-Reload Register (ARR)
O **ARR** define o valor máximo da contagem (o "período"). Quando o contador atinge esse valor, ocorre um evento de **Update** (ou *Overflow*), e o contador reinicia (em modo *up-counting*).
- Em timers de 32 bits (TIM2/5), o ARR permite contagens muito longas sem transbordar rapidamente.

### 3. Contador (CNT)
É o registrador que incrementa ou decrementa a cada pulso de clock processado pelo PSC.

---

# Base de Tempo

Para configurar um timer para gerar um evento a cada **1 segundo**, utilizamos a relação:

$$Tempo (s) = \frac{(PSC + 1) \times (ARR + 1)}{f_{TIM\_CLK}}$$

**Exemplo prático (NUCLEO-G474RE a 170 MHz):**
Para obter uma interrupção de **1 Hz** (1 segundo):
- **Clock:** 170.000.000 Hz
- **PSC:** 16.999 (Divide por 17.000 $\rightarrow$ Clock interno = 10 kHz)
- **ARR:** 9.999 (Conta 10.000 pulsos de 10 kHz $\rightarrow$ 1 segundo)

---

# Interrupções com Timer

Os timers podem gerar diversos gatilhos de interrupção enviados ao **NVIC** (Nested Vectored Interrupt Controller):
- **Update Interrupt:** Gerada quando o contador atinge o valor ARR (Overflow);
- **Capture/Compare:** Gerada quando um sinal externo é capturado ou a contagem atinge um valor específico em um canal;
- **Break:** Gerada em eventos de falha para proteção de hardware.

No driver **HAL**, essas interrupções são tratadas por funções de *callback*, como `HAL_TIM_PeriodElapsedCallback()`.

---

# Observações
- Timers de uso geral como **TIM2** e **TIM5** são ideais para medir intervalos longos devido à sua resolução de **32 bits**.
- O **HRTIM** é um periférico especializado para eletrônica de potência, capaz de resoluções na casa dos picossegundos, algo essencial para controle fino de conversores DC-DC.
- O **LPTIM** é o único timer que pode acordar o microcontrolador do modo **Stop** se configurado com o clock LSI ou LSE.

---

# Referências
- **RM0440:** Reference Manual - STM32G4 Series.
- **UM2505:** User Manual - STM32G4 Nucleo-64 boards.
- **Datasheet:** STM32G474xE.

---
**Dica:** Ao utilizar o **STM32CubeMX**, lembre-se de habilitar o clock do timer na aba *Clock Configuration* antes de ajustar os parâmetros PSC e ARR na aba *Configuration*.
