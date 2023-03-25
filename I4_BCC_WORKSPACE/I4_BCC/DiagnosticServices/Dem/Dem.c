#include "Dem.h"
#include "Dem_Types.h"
#include "SystemManager.h"
#include "SystemManager_Types.h"

Dem_DtcType Dem_DtcArray;

StdReturnType Dem_Init();
StdReturnType Dem_DeInit();
void Dem_MainFunction();
void Dem_ProcessSystemFault();
void Dem_ProcessCircuitFault();
void Dem_SetDtc();

StdReturnType Dem_Init()
{

	return E_OK;

}

StdReturnType Dem_DeInit()
{

	return E_OK;

}

void Dem_MainFunction()
{

}

void Dem_ProcessSystemFault()
{

	for(uint8 index = 0; index < 35; index++)
	{

		if(SystemManager_Fault.fault[index] == index + 1)
		{

			Dem_DtcArray.dtcValue[index] = SystemManager_Fault.fault[index];


		}
		else
		{

			/* do nothing */

		}

	}

}

void Dem_ProcessCircuitFault()
{

	uint8 receivedValue = 0; /* rte read */

	for(uint8 index = 35; index <= 72; index++)
	{

		if(receivedValue == index + 1)
		{

			Dem_DtcArray.dtcValue[index] = receivedValue;

		}
		else
		{

			/* do nothing */

		}

	}

}

void Dem_SetDtc()
{

}
