# GPIO do STM32

## Objetivo

Apresentar os conceitos fundamentais de GPIO (*General Purpose Input/Output*) nos microcontroladores STM32, incluindo modos de operação, configurações elétricas, interrupções externas e características específicas das placas **NUCLEO-G474RE**.

---

# Sumário

- [Introdução](#introdução)
- [O que é GPIO](#o-que-é-gpio)
- [Estrutura e Registradores](#estrutura-e-registradores)
- [Modos de Operação](#modos-de-operação)
- [Entrada Digital](#entrada-digital)
- [Saída Digital](#saída-digital)
- [Pull-up e Pull-down](#pull-up-e-pull-down)
- [Velocidade e Toggling](#velocidade-e-toggling)
- [Restrições de Corrente](#restrições-de-corrente)
- [Interrupções Externas (EXTI)](#interrupções-externas-exti)
- [Observações Práticas (NUCLEO-G474RE)](#observações-práticas-nucleo-g474re)
- [Referências](#referências)

---

# Introdução

Os pinos de GPIO são a interface primária entre o microcontrolador e o mundo externo. No STM32G474RE, os GPIOs são mapeados no barramento **AHB2**, o que permite o chaveamento (toggling) extremamente rápido dos pinos.

# O que é GPIO

GPIO refere-se a pinos que podem ser configurados via software para diversas funções digitais ou analógicas. O STM32G474RE oferece até **107 I/Os rápidos**, sendo que a maioria é tolerante a **5 V**.

# Estrutura e Registradores

Cada porta GPIO (Porta A, B, etc.) é controlada por um conjunto de registradores de 32 bits:
*   **Configuração:** `MODER` (modo), `OTYPER` (tipo de saída), `OSPEEDR` (velocidade) e `PUPDR` (pull-up/pull-down).
*   **Dados:** `IDR` (entrada) e `ODR` (saída).
*   **Manipulação Atômica:** O registrador `BSRR` permite definir ou resetar bits individualmente de forma segura, sem risco de interrupção entre a leitura e a escrita.
*   **Bloqueio:** O registrador `LCKR` pode congelar a configuração do pino até o próximo reset do sistema.

# Modos de Operação

Cada pino pode ser configurado individualmente em quatro modos principais através do registrador `MODER`:
1.  **Input:** Entrada digital.
2.  **Output:** Saída digital (Geral).
3.  **Alternate Function (AF):** Conecta o pino a periféricos internos como Timers, UART ou SPI.
4.  **Analog:** Necessário para funções de ADC, DAC, OPAMP e Comparadores, reduzindo o consumo de energia ao desabilitar o trigger Schmitt de entrada.

# Entrada Digital

No modo de entrada, o buffer de saída é desabilitado e o **Trigger de Schmitt** é ativado para garantir níveis lógicos definidos. Os dados presentes no pino são amostrados a cada ciclo do clock AHB e armazenados no registrador `IDR`.

# Saída Digital

Pode ser configurada em dois tipos via `OTYPER`:
*   **Push-Pull:** O pino pode drenar ou fornecer corrente ativamente (níveis 0 e 1).
*   **Open-Drain:** O pino apenas drena corrente (nível 0). O nível alto (Hi-Z) exige um resistor de pull-up externo ou interno.

# Pull-up e Pull-down

Os pinos possuem resistores internos "fracos" (*weak*) que podem ser ativados para evitar estados flutuantes. No STM32G4, esses resistores têm um valor típico de **40 kΩ** (variando entre 25 e 55 kΩ).

# Velocidade e Toggling

A velocidade de subida/descida do sinal (*Slew Rate*) é ajustável via `OSPEEDR` em quatro níveis: **Low, Medium, High e Very High**. No modo *Very High speed*, o pino pode operar em frequências de até **170 MHz** (dependendo da carga capacitiva e tensão).

# Restrições de Corrente

*   **Capacidade Geral:** A maioria dos GPIOs pode drenar ou fornecer até **±8 mA** (podendo chegar a **±20 mA** com níveis de tensão relaxados).
*   **Limite Total:** A soma da corrente de todos os I/Os não deve exceder **150 mA** (total drenado ou fornecido pelo chip).
*   **Pinos Especiais (PC13, PC14, PC15):** Estes pinos são alimentados por uma chave de energia limitada; eles podem drenar no máximo **3 mA** e sua velocidade não deve exceder **2 MHz**. Eles **não devem ser usados** para acionar cargas como LEDs.

# Interrupções Externas (EXTI)

Todos os pinos de GPIO podem gerar interrupções externas através do controlador **EXTI**.
*   Existem **16 linhas EXTI** principais (EXTI0 a EXTI15) compartilhadas entre as portas (ex: PA0, PB0 e PC0 compartilham a linha EXTI0).
*   A seleção de qual porta aciona a linha EXTI é feita via registradores `SYSCFG_EXTICR`.
*   É possível configurar gatilhos por **borda de subida, descida ou ambas**.

# Observações Práticas (NUCLEO-G474RE)

*   **LED de Usuário (LD2):** Conectado ao pino **PA5** (Verde). Escrever "1" acende o LED.
*   **Botão de Usuário (B1):** Conectado por padrão ao pino **PC13** (Azul).
*   **Pinos de Debug:** Após o reset, PA13 (SWDIO) e PA14 (SWCLK) são configurados automaticamente para interface de programação, com pull-up/pull-down internos ativados.

# Referências

*   **RM0440:** Reference Manual - STM32G4 Series.
*   **DS12288:** Datasheet - STM32G474xB/xC/xE.
*   **UM2505:** User Manual - STM32G4 Nucleo-64 boards.
*   **UM2570:** Manual do Driver HAL/LL.

---

Deseja que eu forneça um exemplo de código em C (utilizando a biblioteca HAL) para configurar o **debouncing** de um botão via interrupção?