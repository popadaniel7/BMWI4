/*****************************************
* Project: BCM I4						 *
* Developer: Daniel Popa				 *
* Module: Diagnostic Control	         *
******************************************/
/*****************************************
*		INCLUDE PATHS					 *
******************************************/
#include "DiagCtrl.h"
#include "Rte.h"
/*****************************************
*		END OF INCLUDE PATHS		     *
******************************************/
/*****************************************
*		DEFINES					 		 *
******************************************/
/*****************************************
* 		END OF DEFINES					 *
******************************************/
/*****************************************
*		VARIABLES					 	 *
******************************************/
/* Request value processing variable. */
uint8 DiagCtrl_RequestValue = STD_LOW;
/* Fault value variable. */
uint8 DiagCtrl_FaultValue = STD_LOW;
/*****************************************
*		END OF VARIABLES				 *
******************************************/
/*****************************************
*		FUNCTIONS				 		 *
******************************************/
/* Main function declaration. */
VOID DiagCtrl_MainFunction();
/* Process requested data function declaration. */
VOID DiagCtrl_ProcessRequestedData();
/*****************************************
*		END OF FUNCTIONS				 *
******************************************/
/***********************************************************************************
* Function: DiagCtrl_MainFunction										   		   *
* Description: Application main function.		 		   						   *
************************************************************************************/
VOID DiagCtrl_MainFunction()
{
	DiagCtrl_ProcessRequestedData();
}
/***********************************************************************************
* END OF DiagCtrl_MainFunction										               *
************************************************************************************/
/***********************************************************************************
* Function: DiagCtrl_ProcessRequestedData										   *
* Description: Process the measured requested data.		 		   				   *
************************************************************************************/
VOID DiagCtrl_ProcessRequestedData()
{
	static uint32 LightSensor_RequestedValue = 0;
	static uint32 VibrationSensor_RequestedValue = 0;
	static uint8 BtcUart_FaultValue_One = 0;
	static uint8 BtcUart_FaultValue_Two = 0;
	static uint8 BtcUart_FaultValue_Three = 0;
	static uint8 BtcUart_FaultValue_Four = 0;
	Rte_Read_Adc_AdcPort_Adc_ChannelOne_Buffer(&LightSensor_RequestedValue, 0);
	Rte_Read_Adc_AdcPort_Adc_ChannelOne_Buffer(&VibrationSensor_RequestedValue, 1);
	Rte_Read_SystemManager_SystemManagerPort_SystemManager_Fault(&BtcUart_FaultValue_One, 17);
	Rte_Read_SystemManager_SystemManagerPort_SystemManager_Fault(&BtcUart_FaultValue_Two, 18);
	Rte_Read_SystemManager_SystemManagerPort_SystemManager_Fault(&BtcUart_FaultValue_Three, 19);
	Rte_Read_SystemManager_SystemManagerPort_SystemManager_Fault(&BtcUart_FaultValue_Four, 20);
	if(BtcUart_FaultValue_One != 0 ||
			BtcUart_FaultValue_Two != 0 ||
			BtcUart_FaultValue_Three != 0 ||
			BtcUart_FaultValue_Four != 0)
	{
		Rte_Call_Dem_P_DemPort_Dem_ReceiveFault(DIAGCTRL_BLUETOOTH_MODULE_MALFUNCTION);
	}
	else
	{
		/* do nothing */
	}
	if(LightSensor_RequestedValue < 100)
	{
		Rte_Call_Dem_P_DemPort_Dem_ReceiveFault(DIAGCTRL_LIGHT_SENSOR_MALFUNCTION);
	}
	else
	{
		/* do nothing */
	}
	if(VibrationSensor_RequestedValue < 100)
	{
		Rte_Call_Dem_P_DemPort_Dem_ReceiveFault(DIAGCTRL_VIBRATION_SENSOR_MALFUNCTION);
	}
	else
	{
		/* do nothing */
	}
	if(Rte_P_Tim_TimPort_Tim5_CalculatedDistance_ChannelThree == 0)
	{
		Rte_Call_Dem_P_DemPort_Dem_ReceiveFault(DIAGCTRL_FRONT_PARKING_DISTANCE_SENSOR_MALFUNCTION);
	}
	else
	{
		/* do nothing */
	}
	if(Rte_P_Tim_TimPort_Tim5_CalculatedDistance_ChannelFour == 0)
	{
		Rte_Call_Dem_P_DemPort_Dem_ReceiveFault(DIAGCTRL_REAR_PARKING_DISTANCE_SENSOR_MALFUNCTION);
	}
	else
	{
		/* do nothing */
	}
}
/***********************************************************************************
* END OF DiagCtrl_ProcessRequestedData										       *
************************************************************************************/
