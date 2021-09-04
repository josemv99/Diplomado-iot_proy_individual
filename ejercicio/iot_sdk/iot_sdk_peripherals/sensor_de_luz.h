/*! @file : sensor_de_luz.h
 * @author  Jose Miguel Morales Vega
 * @version 1.0.0
 * @date    4/09/2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_SENSOR_DE_LUZ_H_
#define IOT_SDK_PERIPHERALS_SENSOR_DE_LUZ_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup SENSOR_DE_LUZ
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define SENSOR_DE_LUZ_ADC16_BASE          ADC0
#define SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP 0U
//#define DEMO_ADC16_USER_CHANNEL  23U /* PTE30, ADC0_SE23 */
#define SENSOR_DE_LUZ_ADC16_USER_CHANNEL  3U /* PTE22, ADC0_SE3 */
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
void sensorDeLuzIniciarCaptura(void);

void sensorDeLuzEsperarResultado(void);

uint32_t sensorDeLuzObtenerDatoADC(void);
/** @} */ // end of X SENSOR_DE_LUZ
/** @} */ // end of X PERIPHERALS

#endif /* IOT_SDK_PERIPHERALS_SENSOR_DE_LUZ_H_ */
