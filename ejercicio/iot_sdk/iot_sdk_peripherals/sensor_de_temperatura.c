/*! @file : sensor_de_temperatura.c
 * @author  Jose Miguel Morales Vega
 * @version 1.0.0
 * @date    8/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sensor_de_temperatura.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/
void sensorDeTemperaturaIniciarCaptura(void){
	 ADC16_SetChannelConfig(SENSOR_DE_TEMPERATURA_ADC16_BASE, SENSOR_DE_TEMPERATURA_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[1]);
 }


 void sensorDeTemperaturaEsperarResultado(void){
	 while (0U == (kADC16_ChannelConversionDoneFlag &
	                      ADC16_GetChannelStatusFlags(SENSOR_DE_TEMPERATURA_ADC16_BASE, SENSOR_DE_TEMPERATURA_ADC16_CHANNEL_GROUP)))
	        {
	        }
 }


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 uint32_t sensorDeTemperaturaObtenerDatoADC(void){
 	 sensorDeTemperaturaIniciarCaptura();
 	 sensorDeTemperaturaEsperarResultado();
 	 uint32_t resultadoADC;
 			 resultadoADC = ADC16_GetChannelConversionValue(SENSOR_DE_TEMPERATURA_ADC16_BASE, SENSOR_DE_TEMPERATURA_ADC16_CHANNEL_GROUP);
 			 return(resultadoADC);
  }

