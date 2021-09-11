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
#include "irq_lpuart0.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
enum _ec25_lista_comandos_at {
    kAT = 0,
    kATI,
    kAT_CPIN,
    kAT_CREG,
    kAT_CMGF_1,
    kAT_CMGS,
    kAT_TEXT_MSG_END,
};
/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Local vars
 ******************************************************************************/
//Listado de comando AT disponibles para ser enviados al modem Quectel
const char *ec25_comandos_at[] = {
    "AT",            //comprueba disponibilidad de dispositivo
    "ATI",            //consulta información del modem
    "AT+CPIN?",        //consulta estado de la simcard
    "AT+CREG?",        //consulta estado de la red celular y tecnología usada en red celular
    "AT+CMGF=1",    //asigna modo texto para enviar mensajes
    "AT+CMGS=\"300xxxxxxx\"",//envia mensaje de texto a numero definido
    "Mensaje",         //MENSAJE & CTRL+Z
    };

const char *comandos_control[] = {
    "LED VERDE ON",            //ensiende led
    "LED VERDE OFF",            //apaga el led
    };

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

/*
 * @brief   Application entry point.
 */


int main(void) {
    volatile static int i = 0 ;
    bool boton1,boton2;
    uint32_t sensor_de_luz;
    uint8_t nuevo_byte_lpuart0;
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    PRINTF("Jose Morales Iniciando...\r\n");
    PRINTF("%s\r\n", ec25_comandos_at[kAT_CREG]);
    /* Enter an infinite loop, just incrementing a counter. */
   //LPTMR_StartTimer(LPTMR0);
    while(1) {
    	if (numeroByteDisponiblesBuffer() != 0){
    		nuevo_byte_lpuart0 = pullByteDesdeBuffer();
    		PRINTF("nuevo byte: %c\r\n", nuevo_byte_lpuart0);
    	}
    	if(lptmr0_irq_counter != 0){
    		toggle_led_red();
    		lptmr0_irq_counter=0;
    		i++ ;
    		sensor_de_luz = sensorDeLuzObtenerDatoADC();
    		//PRINTF("la intensidad de luz es: %d\r\n", sensor_de_luz);
            boton1 = boton1LeerEstado();
            boton2 = boton2LeerEstado();
    	}
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
