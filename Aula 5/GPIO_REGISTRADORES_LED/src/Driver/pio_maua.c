/*
 * pio_maua.c
 *
 * Created: 16/03/2016 17:57:12
 *  Author: 11.01298-6
 */ 

#include <asf.h>
#include "pio_maua.h"

void _pio_set_output(	Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_default_level,const uint32_t ul_pull_up_enable){
	p_pio->PIO_PER = (ul_mask);
	p_pio->PIO_WPMR = 0;
	p_pio->PIO_OER  = (ul_mask );
	
	// Acionamento de pull up
	_pio_pull_up(p_pio,ul_mask,ul_pull_up_enable);
	
	
	//setando o valor padrao 
	if(ul_default_level == 0)
	{
		p_pio->PIO_CODR = (ul_mask );
		
	}
	else
	{
		p_pio->PIO_SODR = ul_mask ;
		
	}
}



void _pio_set_input( 	Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_attribute){
	
	//setando o pino como input
	p_pio->PIO_PER = (ul_mask);
	p_pio->PIO_WPMR = 0;
	p_pio->PIO_ODR  = (ul_mask );
	
	//configuracao do pull-up
	if(ul_attribute & ( 1<< PIO_PULLUP)){
		_pio_pull_up(p_pio,ul_mask,1);
	}
	
	
	//Confirguracoes de debounce e deglitch
	if(ul_attribute & ( 1<< PIO_DEBOUNCE)){
		p_pio->PIO_IFER = ( ul_mask);
		p_pio->PIO_IFSCER = (ul_mask);
	}
	if(ul_attribute & ( 1<< PIO_DEGLITCH)){
		p_pio->PIO_IFER = (ul_mask);
		p_pio->PIO_IFSCDR = ( ul_mask);
	}
		
	
}
void _pio_pull_up(	Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_pull_up_enable){
	if(ul_pull_up_enable==1)
		p_pio->PIO_PUER = (ul_mask );
	else
		p_pio->PIO_PUDR = (ul_mask );	
}

void _pio_pull_down( Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_pull_down_enable){
	if(ul_pull_down_enable==1)
		p_pio->PIO_PPDER = (ul_pull_down_enable << ul_mask );
	else
		p_pio->PIO_PPDDR = (1 << ul_mask );
}
void _pio_set (Pio *p_pio,const uint32_t ul_mask){
p_pio->PIO_SODR = (ul_mask );

}
void _pio_clear( Pio *p_pio,const uint32_t ul_mask){
	p_pio->PIO_CODR =  (ul_mask );
}