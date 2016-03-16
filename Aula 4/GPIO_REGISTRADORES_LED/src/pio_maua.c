/*
 * pio_maua.c
 *
 * Created: 16/03/2016 17:57:12
 *  Author: 11.01298-6
 */ 
#include <asf.h>
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
	
}