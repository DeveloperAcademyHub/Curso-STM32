# Curso STM32

Repositório de estudos, anotações e projetos práticos do curso de STM32 ministrado pelo professor Gabriel Moreira Vigiano.

O conteúdo está organizado em:

- `notes/` → anotações do curso em Markdown
- `projects/` → projetos e exemplos práticos
- `docs/` → datasheets, application notes, esquemáticos e referências

---

# Módulos

| Módulo | Anotações |
|---|---|
| 01 | [Microcontroladores e Processadores ARM](notes/01-microcontroladores-arm.md) |
| 02 | [Softwares e Recursos](notes/02-softwares-recursos.md) |
| 03 | [Revisão de Linguagem C](notes/03-linguagem-c.md) |
| 04 | [Ambientes, Projetos e SWD](notes/04-debug-swd.md) |
| 05 | [Bootloader e Customização](notes/05-bootloader.md) |
| 06 | [Clocks do STM32](notes/06-clocks.md) |
| 07 | [GPIO](notes/07-gpio.md) |
| 08 | [Timers](notes/08-timers.md) |
| 09 | [PWM, OC e IC](notes/09-pwm-oc-ic.md) |
| 10 | [ADC](notes/10-adc.md) |
| 11 | [DAC](notes/11-dac.md) |
| 12 | [Watchdog](notes/12-watchdog.md) |
| 13 | [Low Power Modes](notes/13-low-power.md) |
| 14 | [RTC](notes/14-rtc.md) |
| 15 | [USART](notes/15-usart.md) |
| 16 | [I2C](notes/16-i2c.md) |
| 17 | [SPI](notes/17-spi.md) |
| 18 | [FreeRTOS](notes/18-freertos.md) |
| 19 | [LCD 16x2](notes/19-lcd16x2.md) |
| 20 | [SDCard](notes/20-sdcard.md) |
| 21 | [TouchGFX](notes/21-touchgfx.md) |
| 22 | [Nextion Display](notes/22-nextion.md) |
| 23 | [Modbus](notes/23-modbus.md) |
| 24 | [DSP](notes/24-dsp.md) |
| 25 | [CAN](notes/25-can.md) |
| 26 | [CMSIS-DSP](notes/26-cmsis-dsp.md) |
| 27 | [Memória Flash](notes/27-flash.md) |
| 28 | [Bootloader - Sistema de Memória](notes/28-bootloader-memoria.md) |

---

# Ferramentas e Recursos

## STMicroelectronics

- [STMicroelectronics](https://www.st.com/content/st_com/en.html)
- [STM32 MPU Wiki](https://wiki.st.com/stm32mpu)
- [STM32 MCU Wiki](https://wiki.st.com/stm32mcu)
- [HALs disponibilizados pela ST](https://www.st.com/content/st_com/en/search.html#q=hardware%20abstraction%20layer%20-t=resources-page=1)
- [STM32Cube GitHub](https://github.com/STMicroelectronics)
- [STM32CubeIDE Resource Portal](https://wiki.st.com/stm32mcu/index.php?title=STM32CubeIDE:Introduction_to_STM32CubeIDE&sfr=stm32mcu)

## Ferramentas

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)
- [ST-LINK Server](https://www.st.com/en/development-tools/st-link-server.html)

## Boards

### NUCLEO-L476RG

- [Página oficial](https://www.st.com/en/evaluation-tools/nucleo-l476rg.html)
- [Datasheet STM32L476RG](https://www.st.com/resource/en/datasheet/stm32l476je.pdf)
- [Reference Manual RM0351](https://www.st.com/resource/en/reference_manual/rm0351-stm32l47xxx-stm32l48xxx-stm32l49xxx-and-stm32l4axxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Schematic MB1136-C05](https://www.st.com/resource/en/schematic_pack/mb1136-default-c05_schematic.pdf)

### NUCLEO-G474RE

- [Página oficial](https://www.st.com/en/evaluation-tools/nucleo-g474re.html#documentation)
- [Datasheet STM32G474RE](https://www.st.com/en/microcontrollers-microprocessors/stm32g474re.html)
- [Reference Manual RM0440](https://www.st.com/resource/en/reference_manual/rm0440-stm32g4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Schematic MB1367-G474RE-C05](https://www.st.com/resource/en/schematic_pack/mb1367-g474re-c05_schematic.pdf)