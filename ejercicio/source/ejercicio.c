/*! @file : ejercicio.c
 * @author  Jose Miguel Morales Vega
 * @version 0.0.000
 * @date    01/09/2021
 * @brief   Funcion principal main
 * @details
 *			v0.0.000	Proyecto base creado usando MCUXpresso
 *
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "led.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Local vars
 ******************************************************************************/

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

unsigned int test_global_var=100;
float dato_float=3.1416;
/*
 * @brief   Application entry point.
 */
void delay(void){
	uint32_t i;
	for(i=0;i<0xFFFFF;i++){

	}
}
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");
   /* PRINTF("test_global_var: %d\r\n",test_global_var);
    PRINTF("dato_float: %g\r\n",dato_float);*/

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    unsigned char cont_LR = 0;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        led_on_green();
        delay();
        led_off_green();
        delay();
        if (i % 10 == 0){
        	cont_LR++;
        	if (cont_LR % 2 == 0){
        		led_off_red();
        	}else{
        		led_on_red();
        	}
        }
        //PRINTF("i:%u\r\n",i);
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
