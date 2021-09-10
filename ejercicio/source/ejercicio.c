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
#include "sensor_de_temperatura.h"
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
    volatile char boton1_aux, boton2_aux;
    bool boton1,boton2;
    uint32_t sensor_de_luz;
    uint32_t sensor_de_temperatura;
    float volt_temperatura, volt_luz;
    unsigned char temperatura,iluminancia;
    /* Enter an infinite loop, just incrementing a counter. */
    LPTMR_StartTimer(LPTMR0);
    while(1) {
    	if(lptmr0_irq_counter != 0){
    		lptmr0_irq_counter=0;
    		i++ ;
    		sensor_de_temperatura = sensorDeTemperaturaObtenerDatoADC();
    		volt_temperatura = (3 * sensor_de_temperatura)/4095;
    		temperatura = (volt_temperatura * 90)/3.3;
    		sensor_de_luz = sensorDeLuzObtenerDatoADC();
    		volt_luz = (3.3 * sensor_de_luz);
    		iluminancia = (2*(3.3 - volt_luz))*100;
            boton1 = boton1LeerEstado();
            boton2 = boton2LeerEstado();
          if (boton1 && !boton1_aux){
            	boton1_aux = 1;
            	PRINTF("la temperatura es: %d", temperatura);
            	PRINTF(" °C\r\n");
            }
           if (!boton1){
        	   boton1_aux = 0;
           }
             if (boton2 && !boton2_aux){
             	boton2_aux = 1;
            	PRINTF("la intensidad de luz es: %d", iluminancia);
            	PRINTF(" Lux\r\n");
            }
             if (!boton2){
                boton2_aux = 0;
             }
            if (LR_counter == 1000){
            	LR_counter = 0;
            	toggle_led_red();
            }
    	}
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
