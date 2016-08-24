/**
 *	20-UART 
 * Prof. Rafael Corsi
 *
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_clock.h"

/************************************************************************/
/* Configurações                                                        */
/************************************************************************/

#define STRING_EOL    "\r"
#define STRING_VERSAO "-- "BOARD_NAME" --\r\n" \
					  "-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define CONF_UART_BAUDRATE 115200		
#define CONF_UART          CONSOLE_UART

/** 
 * LEDs
 */ 
#define PIN_LED_BLUE	19
#define PORT_LED_BLUE	PIOA
#define ID_LED_BLUE		ID_PIOA
#define MASK_LED_BLUE	(1u << PIN_LED_BLUE)

#define PIN_LED_GREEN 20
#define PORT_LED_GREEN PIOA
#define ID_LED_GREEN ID_PIOA
#define MASK_LED_GREEN (1u << PIN_LED_GREEN)

#define PIN_LED_RED 20
#define PORT_LED_RED PIOC
#define ID_LED_RED ID_PIOC
#define MASK_LED_RED (1u << PIN_LED_RED)

#define Freq_Init_Blink 4	//Hz
#define IRQ_PRIOR_PIO    0

/************************************************************************/
/* Configura UART                                                       */
/************************************************************************/
void config_uart(void){
	
	/* configura pinos */
	gpio_configure_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);
	
	/* ativa clock */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	
	/* Configuração UART */
	const usart_serial_options_t uart_serial_options = {
		.baudrate   = CONF_UART_BAUDRATE,
		.paritytype = UART_MR_PAR_NO,
		.stopbits   = 0
	};
	
	stdio_serial_init((Usart *)CONF_UART, &uart_serial_options);
}
static void configure_tc(void)
{
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	pmc_enable_periph_clk(ID_TC0);

	tc_init(TC0, 0, TC_CMR_CPCTRG | TC_CMR_TCCLKS_TIMER_CLOCK1);
	

	tc_write_rc(TC0, 0, 8192);

	NVIC_EnableIRQ(ID_TC0);
	
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	
	tc_start(TC0,0);
}
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0,0);

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	/** Muda o estado do LED */
	
	if(pio_get_output_data_status(PORT_LED_BLUE , MASK_LED_BLUE) == 0)
	{
		pio_set(PORT_LED_BLUE, (1 << PIN_LED_BLUE));
	}
	else
	{
		pio_clear(PORT_LED_BLUE, (1 << PIN_LED_BLUE));
	}
	
}

/************************************************************************/
/* Display Menu                                                         */
/************************************************************************/
static void display_menu(void)
{
	puts(" 1 : exibe novamente esse menu \n\r"
		 " 2 : Ativa o LED  \n\r"
		 " 3 : Desliga o LED \n\r ");
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{
	uint8_t uc_key;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure LED 1 */
	pmc_enable_periph_clk(ID_LED_BLUE);
	pio_set_output(PORT_LED_BLUE  , MASK_LED_BLUE	,1,0,0);

	/* Initialize debug console */
	config_uart();
	
	/* frase de boas vindas */
	puts(" ---------------------------- \n\r"
	 	 " Bem vindo terraquio !		\n\r"
		 " ---------------------------- \n\r");
		 
	/* display main menu */
	display_menu();
	configure_tc();
	TC0_Handler();
	
	pio_clear(PORT_LED_RED, MASK_LED_RED);
	pio_set(PORT_LED_GREEN, MASK_LED_GREEN);
	
	PIOA->PIO_PER = (1 << PIN_LED_BLUE );
	PIOA->PIO_OER |=  (1 << PIN_LED_BLUE );
	
	
	PMC->PMC_PCER0 |= ID_PIOC;
	PIOC->PIO_PER |= (1 << PIN_LED_RED );
	PIOC->PIO_OER |=  (1 << PIN_LED_RED );
	
	
				tc_stop(TC0, 0);
	PIOA->PIO_SODR = (1 << PIN_LED_BLUE );
	PIOC->PIO_CODR = (1 << PIN_LED_RED );
	
	while (1) {
		usart_serial_getchar((Usart *)CONSOLE_UART, &uc_key);	
		switch (uc_key) {
			case '1':
				display_menu();
				break;
			case '2':
				configure_tc();
				PIOA->PIO_CODR = (1 << PIN_LED_BLUE );
				
				puts("Led BLUE ON \n\r");
				break;
			case '3' :
				tc_stop(TC0, 0);
				PIOA->PIO_SODR = (1 << PIN_LED_BLUE );
				puts("Led BLUE OFF \n\r");
				break;
			case '4':
				tc_start(TC0,0);
				pio_clear(PORT_LED_GREEN, MASK_LED_GREEN);
				puts("Led GREEN ON \n\r");
				break;
			case '5' :
				tc_stop(TC0, 0);

				pio_set(PORT_LED_GREEN, MASK_LED_GREEN);
				puts("Led GREEN OFF \n\r");
				break;
			case '6':
					tc_start(TC0,0);
					PIOC->PIO_SODR = (1 << PIN_LED_RED );
				
				puts("Led RED ON \n\r");
			break;
			case '7' :
				tc_stop(TC0, 0);
				PIOC->PIO_CODR = (1 << PIN_LED_RED );
				puts("Led RED OFF \n\r");
			break;
			case '8' :
				tc_start(TC0,0);
				tc_write_rc(TC0, 0, tc_read_rc(TC0,0) * 0.5);
				puts("aumentando \n\r");
				break;
			case '9' :
				
				tc_write_rc(TC0, 0, tc_read_rc(TC0,0) * 1.4);
				puts("diminuindo \n\r");
				break;				
			default:
				printf("Opcao nao definida: %d \n\r", uc_key);
		}	
	}
}
