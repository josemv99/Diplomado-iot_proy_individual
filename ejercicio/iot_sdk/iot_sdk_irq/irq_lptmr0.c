/*! @file : irq_lptmr0.c
 * @author  Jose Miguel Morales Vega
 * @version 1.0.0
 * @date    4/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "irq_lptmr0.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/
volatile uint32_t lptmr0_irq_counter;
volatile uint32_t LR_counter;
/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void LPTMR0_IRQHANDLER(void) {
  uint32_t intStatus;
  /* Reading all interrupt flags of status register */
  intStatus = LPTMR_GetStatusFlags(LPTMR0_PERIPHERAL);
  LPTMR_ClearStatusFlags(LPTMR0_PERIPHERAL, intStatus);

  lptmr0_irq_counter++;
  LR_counter +=10;

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 
