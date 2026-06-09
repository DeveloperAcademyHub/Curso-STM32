# ADC (Conversor Analógico-Digital)

## Objetivo

Apresentar os conceitos fundamentais do ADC (*Analog-to-Digital Converter*) presente em microcontroladores STM32.

## Sumário

- [Introdução](#introdução)
- [Funcionamento Básico](#funcionamento-básico)
- [Resolução](#resolução)
- [Interrupção do ADC](#interrupção-do-adc)
- [DMA](#dma)
- [Configuração no STM32CubeMX](#configuração-no-stm32cubemx)
- [Inicialização via HAL](#inicialização-via-hal)
- [Teorema da Amostragem](#teorema-da-amostragem)
- [Conversão Simultânea](#conversão-simultânea)
- [Auto Calibração](#auto-calibração)

---

# Introdução
O periférico ADC no STM32 é um conversor de **aproximações sucessivas (SAR)**. Ele é projetado para converter sinais de tensão analógicos (geralmente entre 0 e $V_{REF+}$) em valores digitais processáveis pela CPU.
*   **Série G4:** Possui até 5 ADCs independentes de 12 bits, com taxas de até 4 Msps.
*   **Série L4:** Oferece até 3 ADCs de 12 bits com baixo consumo e taxas de até 5,33 Msps.

# Funcionamento Básico
O ADC opera através de multiplexação de canais, permitindo medir múltiplas fontes externas (pinos GPIO) e internas (sensor de temperatura, $V_{REFINT}$, $V_{BAT}$).
*   **Grupos de Conversão:**
    *   **Regular:** Sequência de até 16 canais executados em segundo plano.
    *   **Injetado:** Sequência de até 4 canais com **prioridade mais alta**, capaz de interromper o grupo regular para conversões críticas de tempo real.
*   **Modos de Disparo:** As conversões podem ser iniciadas por software ou por gatilhos de hardware (timers ou eventos externos EXTI).

# Resolução
A resolução nativa é de **12 bits**, mas pode ser configurada para **10, 8 ou 6 bits** para aumentar a velocidade de conversão.
*   **Oversampling:** Ambas as séries possuem uma unidade de oversampling por hardware que permite atingir uma resolução equivalente de até **16 bits**, melhorando a relação sinal-ruído (SNR) e filtrando ruídos.

# Interrupção do ADC
O ADC pode gerar interrupções no **NVIC** para diversos eventos, permitindo que a CPU gerencie os dados sem polling constante. Os principais flags são:
*   **ADRDY:** ADC pronto para operar.
*   **EOC / JEOC:** Fim de conversão (regular ou injetada).
*   **EOS / JEOS:** Fim de uma sequência completa de conversões.
*   **OVR:** Overrun de dados (novo dado chegou antes do anterior ser lido).
*   **AWD (Analog Watchdog):** Dispara se a tensão monitorada sair de uma faixa programada.

# DMA
O uso do **DMA (Direct Memory Access)** é altamente recomendado para grupos regulares com múltiplos canais. O DMA transfere automaticamente cada resultado do registrador `ADC_DR` para um buffer na RAM, evitando que a CPU seja sobrecarregada ou que ocorram erros de *overrun*.
*   Suporta modos **one-shot** (para um número fixo de dados) ou **circular** (para fluxos contínuos).

# Configuração no STM32CubeMX
1.  **Analog:** Habilitar o ADC e os canais desejados.
2.  **Clock:** Configurar o prescaler do ADC no domínio de clock síncrono ou assíncrono.
3.  **GPIO:** O CubeMX configura automaticamente os pinos em **modo analógico**.
4.  **Sampling Time:** Ajustar o tempo de amostragem por canal para garantir a carga correta do capacitor interno.
5.  **DMA/Interrupts:** Adicionar canais DMA ou habilitar interrupções conforme a necessidade.

# Inicialização via HAL
A biblioteca HAL utiliza um fluxo padronizado:
*   `HAL_ADC_Init()`: Configura a resolução, alinhamento e sequenciador.
*   `HAL_ADC_ConfigChannel()`: Define o tempo de amostragem e a posição do canal na sequência.
*   **Início das Conversões:**
    *   `HAL_ADC_Start()`: Modo polling.
    *   `HAL_ADC_Start_IT()`: Modo interrupção.
    *   `HAL_ADC_Start_DMA()`: Modo DMA.

# Teorema da Amostragem
Embora os manuais não citem Nyquist nominalmente, eles definem os limites físicos de amostragem ($f_s$). A taxa de amostragem deve respeitar o tempo total: $T_{CONV} = \text{Sampling Time} + \text{Successive Approximation Time}$. Para sinais variáveis, $f_s$ deve ser pelo menos o dobro da maior frequência do sinal analógico para evitar aliasing.

# Conversão Simultânea
Em microcontroladores com múltiplos ADCs (como G4 e L4), é possível utilizar o **Dual ADC Mode**.
*   O ADC1 (mestre) dispara simultaneamente o ADC2 (escravo).
*   Os dados de ambos os ADCs podem ser lidos de forma combinada através do registrador comum **ADCx_CDR**.
*   Isso é ideal para medir simultaneamente corrente e tensão em sistemas de controle de potência.

# Auto Calibração
Os ADCs possuem um mecanismo de **auto calibração** para compensar variações de offset causadas por temperatura ou alimentação.
*   Deve ser executada preferencialmente após cada inicialização do chip.
*   A calibração só pode ser iniciada com o ADC desabilitado (`ADEN = 0`).
*   HAL: `HAL_ADCEx_Calibration_Start()`.