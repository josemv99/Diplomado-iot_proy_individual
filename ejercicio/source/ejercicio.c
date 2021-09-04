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
#include "sensor_de_luz.h"
#include "irq_lptmr0.h"
#include "botones.h"
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


int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    bool boton1,boton2;
    uint32_t sensor_de_luz;
    /* Enter an infinite loop, just incrementing a counter. */
    LPTMR_StartTimer(LPTMR0);
    while(1) {
    	if(lptmr0_irq_counter != 0){
    		toggle_led_red();
    		lptmr0_irq_counter=0;
            i++ ;
            sensor_de_luz = sensorDeLuzObtenerDatoADC();
            //PRINTF("adc: %u\r\n ", sensor_de_luz);
            boton1 = boton1LeerEstado();
            boton2 = boton2LeerEstado();
            PRINTF("boton1: %u\r\n",boton1);
            PRINTF("boton2: %u\r\n",boton2);
    	}
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
