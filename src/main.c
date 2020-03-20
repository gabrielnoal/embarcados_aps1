/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        ID_PIOC              // ID do perif�rico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define BUT_PIO           PIOA                 // periferico que controla o BUTTON
#define BUT_PIO_ID        ID_PIOA              // ID do perif�rico PIOC (controla BUTTON)
#define BUT_PIO_IDX       11                   // ID do BUTTON no PIO
#define BUT_PIO_IDX_MASK  (1 << BUT_PIO_IDX)   // Mascara para CONTROLARMOS o LED

//LED 1
#define OLED_LED1_PIO	  PIOA
#define OLED_LED1_PIO_ID  ID_PIOA
#define OLED_LED1_PIO_IDX 0
#define OLED_LED1_PIO_IDX_MASK (1 << OLED_LED1_PIO_IDX)

//LED2
#define OLED_LED2_PIO	  PIOC
#define OLED_LED2_PIO_ID  ID_PIOC
#define OLED_LED2_PIO_IDX 30
#define OLED_LED2_PIO_IDX_MASK (1 << OLED_LED2_PIO_IDX)

//LED3
#define OLED_LED3_PIO	  PIOB
#define OLED_LED3_PIO_ID  ID_PIOB
#define OLED_LED3_PIO_IDX 2
#define OLED_LED3_PIO_IDX_MASK (1 << OLED_LED3_PIO_IDX)

//BOTÃO 1
#define OLED_BUT1_PIO	  PIOD
#define OLED_BUT1_PIO_ID  ID_PIOD
#define OLED_BUT1_PIO_IDX 28
#define OLED_BUT1_PIO_IDX_MASK (1 << OLED_BUT1_PIO_IDX)

//BOTÃO 2
#define OLED_BUT2_PIO	  PIOC
#define OLED_BUT2_PIO_ID  ID_PIOC
#define OLED_BUT2_PIO_IDX 31
#define OLED_BUT2_PIO_IDX_MASK (1 << OLED_BUT2_PIO_IDX)

//BOTÃO 3
#define OLED_BUT3_PIO	  PIOA
#define OLED_BUT3_PIO_ID  ID_PIOA
#define OLED_BUT3_PIO_IDX 19
#define OLED_BUT3_PIO_IDX_MASK (1 << OLED_BUT3_PIO_IDX)

/************************************************************************/
/* constants                                                            */
/************************************************************************/
typedef struct {
	Pio *pio;
	int pio_id;
	int id;
	int mask;
} component;

component led1 = {
	OLED_LED1_PIO,
	OLED_LED1_PIO_ID,
	OLED_LED1_PIO_IDX,
	OLED_LED1_PIO_IDX_MASK
};
component led2 = {
	OLED_LED2_PIO,
	OLED_LED2_PIO_ID,
	OLED_LED2_PIO_IDX,
	OLED_LED2_PIO_IDX_MASK
};
component led3 = {
	OLED_LED3_PIO,
	OLED_LED3_PIO_ID,
	OLED_LED3_PIO_IDX,
	OLED_LED3_PIO_IDX_MASK
};

component prevButton = {
	OLED_BUT1_PIO,
	OLED_BUT1_PIO_ID,
	OLED_BUT1_PIO_IDX,
	OLED_BUT1_PIO_IDX_MASK,
};
component playButton = {
	OLED_BUT2_PIO,
	OLED_BUT2_PIO_ID,
	OLED_BUT2_PIO_IDX,
	OLED_BUT2_PIO_IDX_MASK,
};
component nextButton = {
	OLED_BUT3_PIO,
	OLED_BUT3_PIO_ID,
	OLED_BUT3_PIO_IDX,
	OLED_BUT3_PIO_IDX_MASK,
};

typedef struct {
	component buttons[3];
	component leds[3];
} components;

typedef void (*voidFunction)(void);

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

volatile int play;
volatile int musicIndex;

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);
void prevButtonFunction(void);
void playButtonFunction(void);
void nextButtonFunction(void);
void enebleAllPeriph(int periphIdsList[], int size);
void configureLeds(component leds[], int size);
void configureButtons(component buttons[], int size);
void turnOnLED(component led);
void turnOffLED(component led);
void changeMusic(int index);
void writeLCD(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/
void turnOnLED(component led){
	pio_clear(led.pio, led.mask);
}

void turnOffLED(component led){
	pio_set(led.pio, led.mask);
}

void writeLCD(void){
	char string[128];
	if (play){
		sprintf(string, "Musica: %d", musicIndex + 1);
		} else {
		sprintf(string, "Pause     ");
	}
	gfx_mono_draw_string(string, 0,16, &sysfont);
}

void prevButtonFunction(void) {
	changeMusic(0);
	writeLCD();
	turnOnLED(led1);
	delay_ms(200);
	turnOffLED(led1);
}

void playButtonFunction(void) {
	play = !play;
	writeLCD();
	turnOnLED(led2);
	delay_ms(200);
	turnOffLED(led2);
}

void nextButtonFunction(void) {
	changeMusic(1);
	writeLCD();
	turnOnLED(led3);
	delay_ms(200);
	turnOffLED(led3);
}

void changeMusic(int next){
	if (next){
		if (musicIndex == 2){
			musicIndex = 0;
		} else {
			musicIndex += 1;
		}
	} else {
		if (musicIndex == 0){
			musicIndex = 2;
			} else {
			musicIndex -= 1;
		}
	}
}
/************************************************************************/
/* funcoes                                                              */
/************************************************************************/
void enebleAllPeriph(int periphIdsList[], int size){

	
	for (int i = 0; i <size; i++)
	{
		pmc_enable_periph_clk(periphIdsList[i]);
	}
}


void configureLeds(component leds[], int size){

	for (int i = 0; i < size; i++)
	{
		component led = leds[i];
		pio_configure(led.pio, PIO_OUTPUT_1, led.mask, PIO_DEFAULT);
	}
}

void configureButtons(component buttons[], int size){
	voidFunction buttonsFunctions[3] = {
		prevButtonFunction,
		playButtonFunction,
		nextButtonFunction
	};
	for (int i = 0; i < size; i++)
	{
		component button = buttons[i];
		pio_configure(button.pio, PIO_INPUT, button.mask, PIO_PULLUP | PIO_DEBOUNCE );
		// Configura interrupção no pino referente ao botao e associa
		// função de callback caso uma interrupção for gerada
		pio_handler_set(
			button.pio,
			button.pio_id,
			button.mask,
			PIO_IT_FALL_EDGE,
			buttonsFunctions[i]
		);
		// Ativa interrupção
		pio_enable_interrupt(button.pio, button.mask);
			
		// Configura NVIC para receber interrupcoes do PIO do botao
		// com prioridade i (quanto mais próximo de 0 maior)
		NVIC_EnableIRQ(button.pio_id);
		NVIC_SetPriority(button.pio_id, 4); // Prioridade 4
	}
}

// Função de inicialização do uC
void init(void){
	board_init();
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	int periphIdsList[4] = {
		ID_PIOA,
		ID_PIOB,
		ID_PIOC,
		ID_PIOD
	};
	enebleAllPeriph(periphIdsList, 4);
	
	
	components myBoardComponents = {
		{
			prevButton,
			playButton,
			nextButton,
		},
		{
			led1,
			led2,
			led3,
		},
	};
	
	
	//Configura os LEDs
	configureLeds(myBoardComponents.leds, 3);

	//Configura os botões
	configureButtons(myBoardComponents.buttons, 3);
	
	play = 0;
	musicIndex = 0;
	
	delay_init();
	//Init OLED Screen
	gfx_mono_ssd1306_init();

}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main (void)
{
	init();
	playButtonFunction();

  /* Insert application code here, after the board has been initialized. */
	while(1) {

	}
}