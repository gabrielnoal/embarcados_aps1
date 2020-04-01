# Resumo :

Esse exemplo demonstra o controle do módulo de `OLED 1 XPLAINED PRO`  via interface SPI (Serial Peripheral Interface Bus).

Periféricos uC:

    - Power Managment Controller (PMC)
    - Serial Protocol Interface (SPI)
 
APIs :

    - Driver SSD1306
 
Módulos : 

    - OLED 1 XPLAINED PRO
    - BUZZER

# Utilizando

    - Conecte o ATMELSAME70 com o pc/notebook e abra o arquivo chamado spi_teste dentro da pasta do projeto, dentro do 
    projeto, abra o main.pc e compile, logo após deve-se utilizar o Hardware para testes do projeto.

# Estruturação

    - O projeto foi estruturado a partir de uma pasta fornecida pelo professor, a qual somente o arquivo main.c foi alterado
    , enquanto o pitches.h foi adicionado.

## Diagrama

    - OLED :
        - LED1 : PA0
        - LED2 : PC30
        - LED3 : PB2
        - BUT1 : PD28
        - BUT2 : PC31
        - BUT3 : PA19
    - BUZZER :
        - + : PC13
        - : GND

![](diagrama.png)

## Resultado

    - https://www.youtube.com/watch?v=_54ECtpbAFI

![](final.jpeg)

