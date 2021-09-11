/*! @file : irq_lpuart0.c
 * @author  Jose Miguel Morales Vega
 * @version 1.0.0
 * @date    11/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "irq_lpuart0.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
void nuevoDatoLpuart0(uint8_t nuevo_byte);

/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/
volatile uint8_t rx_ring_buffer[RX_RING_BUFFER_SIZE];
volatile uint32_t rx_index_productor;
volatile uint32_t rx_index_consumidor;
uint32_t lpuart_irq_counter;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void nuevoDatoLpuart0(uint8_t nuevo_byte){
    if (((rx_index_productor + 1) % RX_RING_BUFFER_SIZE) != rx_index_consumidor){
  	  rx_ring_buffer[rx_index_productor] = nuevo_byte;
  	  rx_index_productor++;
  	  rx_index_productor %= RX_RING_BUFFER_SIZE;
    }
}

/* LPUART0_IRQn interrupt handler */
void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
  uint32_t intStatus;
  uint8_t dato_lpuart;
  /* Reading all interrupt flags of status registers */
  intStatus = LPUART_GetStatusFlags(LPUART0_PERIPHERAL);

  /* Flags can be cleared by reading the status register and reading/writing data registers.
    See the reference manual for details of each flag.
    The LPUART_ClearStatusFlags() function can be also used for clearing of flags in case the content of data/FIFO regsiter is not used.
    For example:
        status_t status;
        status = LPUART_ClearStatusFlags(LPUART0_PERIPHERAL, intStatus);
  */

  /* Place your code here */

      /* If new data arrived. */
      if ((kLPUART_RxDataRegFullFlag)&intStatus)
      {
    	  dato_lpuart = LPUART_ReadByte(LPUART0);
    	  nuevoDatoLpuart0(dato_lpuart);

      }
      SDK_ISR_EXIT_BARRIER;


  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
uint8_t pullByteDesdeBuffer(){
	uint8_t byte_a_retornar;
	if (rx_index_productor != rx_index_consumidor){
		byte_a_retornar = rx_ring_buffer[rx_index_consumidor];
		rx_index_consumidor++;
		rx_index_consumidor %= RX_RING_BUFFER_SIZE;
	}
	return(byte_a_retornar);
}

int32_t numeroByteDisponiblesBuffer(){
	return((int32_t)(rx_index_productor - rx_index_consumidor));
}

