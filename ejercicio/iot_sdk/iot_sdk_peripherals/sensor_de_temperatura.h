/*! @file : sensor_de_temperatura.h
 * @author  Jose Miguel Morales Vega
 * @version 1.0.0
 * @date    8/09/2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_SENSOR_DE_TEMPERATURA_H_
#define IOT_SDK_PERIPHERALS_SENSOR_DE_TEMPERATURA_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup SENSOR DE TEMPERATURA
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/
#define SENSOR_DE_TEMPERATURA_ADC16_BASE          ADC0
#define SENSOR_DE_TEMPERATURA_ADC16_CHANNEL_GROUP 0U
#define SENSOR_DE_TEMPERATURA_ADC16_USER_CHANNEL  26U /* , ADC0_SE26 */

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/
void sensorDeTemperaturaIniciarCaptura(void);

void sensorDeTemperaturaEsperarResultado(void);

uint32_t sensorDeTemperaturaObtenerDatoADC(void);

/** @} */ // end of X SENSOR DE TEMPERATURA
/** @} */ // end of X PERIPHERALS

#endif /* IOT_SDK_PERIPHERALS_SENSOR_DE_TEMPERATURA_H_ */
