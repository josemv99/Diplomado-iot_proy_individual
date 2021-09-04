/*! @file : sensor_de_luz.c
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
#include "sensor_de_luz.h"

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
 void sensorDeLuzIniciarCaptura(void){
	 ADC16_SetChannelConfig(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[0]);
 }


 void sensorDeLuzEsperarResultado(void){
	 while (0U == (kADC16_ChannelConversionDoneFlag &
	                      ADC16_GetChannelStatusFlags(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP)))
	        {
	        }
 }

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 

uint32_t sensorDeLuzObtenerDatoADC(void){
	 sensorDeLuzIniciarCaptura();
	 sensorDeLuzEsperarResultado();
	 uint32_t resultadoADC;
			 resultadoADC = ADC16_GetChannelConversionValue(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP);
			 return(resultadoADC);
 }
