/*
 * pio_maua.c
 *
 * Created: 16/03/2016 17:57:12
 *  Author: 11.01298-6
 */ 

#include <asf.h>
#include "pio_maua.h"

void _pio_set_output(	Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_default_level,const uint32_t ul_pull_up_enable){
	p_pio->PIO_PER = (1 << ul_mask);
	p_pio->PIO_WPMR = 0;
	p_pio->PIO_ODR  = (1 << ul_mask );
	if(ul_pull_up_enable==1)
	p_pio->PIO_PUER = (ul_pull_up_enable << ul_mask );
	else
	p_pio->PIO_PER = (1 << ul_mask );
	
}
void _pio_set_input( 	Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_attribute){
	
}
void _pio_pull_up(	Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_pull_up_enable){
	
}
void _pio_pull_down( Pio *p_pio,const uint32_t ul_mask,const uint32_t ul_pull_down_enable){
	
}