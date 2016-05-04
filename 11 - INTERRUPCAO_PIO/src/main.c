/**
 * IMT - Rafael Corsi
 * 
 * Interrup��o
*/

#include <asf.h>
#include "Driver/pio_maua.h"
#include "Driver/pmc_maua.h"

/*
 * Prototypes
 */

static void push_button_handle(uint32_t id, uint32_t mask);


/** 
 * Defini��o dos pinos
 * Pinos do uC referente aos LEDS/ Bot�o
 *
 * O n�mero referente ao pino (PIOAxx), refere-se ao
 * bit que deve ser configurado no registrador para alterar
 * o estado desse bit espec�fico.
 *
 * exe : O pino PIOA_19 � configurado nos registradores pelo bit
 * 19. O registrador PIO_SODR configura se os pinos ser�o n�vel alto.
 * Nesse caso o bit 19 desse registrador � referente ao pino PIOA_19
 *
 * ----------------------------------
 * | BIT 19  | BIT 18  | ... |BIT 0 |
 * ----------------------------------
 * | PIOA_19 | PIOA_18 | ... |PIOA_0|
 * ----------------------------------
 */
#define PIN_LED_BLUE	19
#define PIN_LED_RED		20
#define PIN_LED_GREEN	20
#define PIN_BUTTON		3
#define time			100

/** 
 * Defini��o dos ports
 * Ports referentes a cada pino
 */
#define PORT_LED_BLUE	PIOA
#define PORT_LED_GREEN	PIOA
#define PORT_LED_RED	PIOC
#define PORT_BUT_2		PIOB

/**
 * Define os IDs dos perif�ricos associados aos pinos
 */
#define ID_LED_BLUE		ID_PIOA
#define ID_LED_GREEN	ID_PIOA
#define ID_LED_RED		ID_PIOC
#define ID_BUT_2		ID_PIOB

/**
 *	Define as masks utilziadas
 */
#define MASK_LED_BLUE	(1u << PIN_LED_BLUE)
#define MASK_LED_GREEN	(1u << PIN_LED_GREEN)
#define MASK_LED_RED	(1u << PIN_LED_RED)
#define MASK_BUT_2		(1u << PIN_BUT_2)

/************************************************************************/
/*  INTERRUP��O PORTB													*/
/************************************************************************/

static void push_button_handle(uint32_t id, uint32_t mask){
	pio_clear(PIOA, (1 << PIN_LED_GREEN));
}


/**
 * Main function
 * 1. configura o clock do sistema
 * 2. desabilita wathdog
 * 3. Configura os LEDs como sa�da
 * 4. Configura o bot�o como entrada
 * 5. Configura a interrup��o no bot�o
 * 6. Configura a interrup��o no NVIC/CORE
 * 7. Ativa interrup��o
 * 8. while(1)
 * 
 * 9. Quando o bot�o for apertado, a fun��o push_button_handle � chamada via interrup��o
 */

int main (void)
{

	/**
	* Inicializando o clock do uP
	*/
	sysclk_init();
	
	/** 
	*  Desabilitando o WathDog do uP
	*/
	WDT->WDT_MR = WDT_MR_WDDIS;
		
	/**
	* Ativa clock nos perif�ricos
	*/
	_pmc_enable_clock_periferico(ID_LED_BLUE);
	_pmc_enable_clock_periferico(ID_LED_GREEN);		// Redundante mas n�o tem problema !
	_pmc_enable_clock_periferico(ID_LED_RED);
	_pmc_enable_clock_periferico(ID_BUT_2);
				
	/**
	*	Configura sa�da
	*/
	pio_set_output(PORT_LED_BLUE  , MASK_LED_BLUE	,1,0,0);
	pio_set_output(PORT_LED_GREEN , MASK_LED_GREEN  ,1,0,0);
	pio_set_output(PORT_LED_RED	  , MASK_LED_RED	,1,0,0);
	
	/**
	* Configura entrada
	*/ 
	pio_set_input(PORT_BUT_2, MASK_BUT_2, PIO_PULLUP | PIO_DEBOUNCE);
	
	/*
	 * Configura divisor do clock para debounce
	 */
	//pio_set_debounce_filter(???, ???, ???);
	
	/* 
	*	Configura interrup��o para acontecer em borda de descida.
	*/
	//pio_handler_set(???, 
	//				???,
	//				???,  
	//				???,
	//				???);
				
	/*
	*	Ativa interrup��o no perif�rico B porta do bot�o
	*/	
	//pio_enable_interrupt(???,??? );
	
	/*
	*	Configura a prioridade da interrup��o no pORTB
	*/
	//NVIC_SetPriority((IRQn_Type), ??? );
	
	/*
	*	Ativa interrup��o no port B
	*/
	//NVIC_EnableIRQ((IRQn_Type) ???);
	
	/**
	*	Loop infinito
	*/
	while(1){
		pio_set(PIOA, (1 << PIN_LED_BLUE));
		delay_ms(500);
		pio_clear(PIOA, (1 << PIN_LED_BLUE));
		delay_ms(500);
	}
}

