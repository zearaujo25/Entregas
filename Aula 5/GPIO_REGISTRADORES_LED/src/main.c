/**
 * IMT - Rafael Corsi
 * 
 * PIO - 07
 *  Configura o PIO do SAM4S (Banco A, pino 19) para operar em
 *  modo de output. Esse pino est� conectado a um LED, que em 
 *  l�gica alta apaga e l�gica baixa acende.
*/

#include <asf.h>
#include "Driver/pio_maua.h"
#include "Driver/pmc_maua.h"

/*
 * Prototypes
 */

/** 
 * Defini��o dos pinos
 * Pinos do uC referente aos LEDS.
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
#define PIN_LED_BLUE 19
#define PIN_LED_RED 20
#define PIN_LED_GREEN 20
#define PIN_PUSHBUTTON_2 3
/** 
 * Defini��o dos ports
 * Ports referentes a cada pino
 */
#define PORT_LED_BLUE PIOA
#define PORT_LED_RED PIOC
#define PORT_LED_GREEN PIOA
#define PORT_PUSHBUTTON_2 PIOB

/**
 * Main function
 * 1. configura o clock do sistema
 * 2. desabilita wathdog
 * 3. ativa o clock para o PIOA
 * 4. ativa o controle do pino ao PIO
 * 5. desabilita a prote��o contra grava��es do registradores
 * 6. ativa a o pino como modo output
 * 7. coloca o HIGH no pino
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
		
	// 29.17.4 PMC Peripheral Clock Enable Register 0
	// 1: Enables the corresponding peripheral clock.
	// ID_PIOA = 11 - TAB 11-1
	//PMC->PMC_PCER0 |= (1<<ID_PIOA) | (1<<ID_PIOB);
	_pmc_enable_clock_periferico(ID_PIOA);
	_pmc_enable_clock_periferico(ID_PIOB);
	
	//PMC->PMC_PCER0 |= ID_PIOC;
	 //31.6.1 PIO Enable Register
	// 1: Enables the PIO to control the corresponding pin (disables peripheral control of the pin).	
	//PIOA->PIO_PER = (1 << PIN_LED_BLUE );
	//PIOB->PIO_PER = (1 << PIN_PUSHBUTTON_2 );
	
	//PIOA->PIO_PER |= (1 << PIN_LED_GREEN );
	//PIOC->PIO_PER |= (1 << PIN_LED_RED );
	// 31.6.46 PIO Write Protection Mode Register
	// 0: Disables the write protection if WPKEY corresponds to 0x50494F (PIO in ASCII).
	//PIOA->PIO_WPMR = 0;
	//PIOB->PIO_WPMR = 0;
	
	//PIOB->PIO_ODR  = (1 << PIN_PUSHBUTTON_2 );
	//PIOB->PIO_PUER = (1 << PIN_PUSHBUTTON_2 );

	
	// 31.6.4 PIO Output Enable Register
	// 1: Enables the output on the I/O line.
	//PIOA->PIO_OER |=  (1 << PIN_LED_BLUE );
	//PIOA->PIO_OER |=  (1 << PIN_LED_GREEN );
	//PIOC->PIO_OER |=  (1 << PIN_LED_RED );

	// 31.6.10 PIO Set Output Data Register
	// 1: Sets the data to be driven on the I/O line.
	
	_pio_set_output(PIOA,(1 << PIN_LED_BLUE ), 1, 0);
	_pio_set_input(PIOB, 1<<PIN_PUSHBUTTON_2,1);

	/**
	*	Loop infinito
	*/
		while(1){
		
            /*
             * Utilize a fun��o delay_ms para fazer o led piscar na frequ�ncia
             * escolhida por voc�.
             */
			
		if(((PIOB->PIO_PDSR >> PIN_PUSHBUTTON_2) & 1) == 1)
		{
			_pio_set(PIOA,1<<PIN_LED_BLUE);
			//PIOA->PIO_SODR =  (1 << PIN_LED_BLUE );
		}
		else
		{
			_pio_clear(PIOA,1<<PIN_LED_BLUE);
			
			//PIOA->PIO_CODR =  (1 << PIN_LED_BLUE );
			
		}	
		
		
	}
}



