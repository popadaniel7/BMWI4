#include "main.h"

int main()
{

	SystemManager_Init();

	osKernelInitialize();

	MX_FREERTOS_Init();

	osKernelStart();

}
