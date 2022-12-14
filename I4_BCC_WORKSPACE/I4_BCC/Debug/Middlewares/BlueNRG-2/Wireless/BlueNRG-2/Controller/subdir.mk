################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.c \
C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.c \
C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.c \
C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.c 

OBJS += \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.o \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.o 

C_DEPS += \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.d \
./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.o: C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gap_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32_THREAD_SAFE_STRATEGY=4 '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -c -I../Core/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../BlueNRG-2/Target -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/utils -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/includes -I../Core/ThreadSafe -I../MBEDTLS/App -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include/mbedtls -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.o: C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_gatt_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32_THREAD_SAFE_STRATEGY=4 '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -c -I../Core/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../BlueNRG-2/Target -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/utils -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/includes -I../Core/ThreadSafe -I../MBEDTLS/App -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include/mbedtls -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.o: C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_hal_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32_THREAD_SAFE_STRATEGY=4 '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -c -I../Core/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../BlueNRG-2/Target -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/utils -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/includes -I../Core/ThreadSafe -I../MBEDTLS/App -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include/mbedtls -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.o: C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/controller/bluenrg1_l2cap_aci.c Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32_THREAD_SAFE_STRATEGY=4 '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -c -I../Core/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../BlueNRG-2/Target -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/hci/hci_tl_patterns/Basic -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/utils -IC:/Users/Daniel/STM32Cube/Repository//Packs/STMicroelectronics/X-CUBE-BLE2/3.3.0/Middlewares/ST/BlueNRG-2/includes -I../Core/ThreadSafe -I../MBEDTLS/App -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include/mbedtls -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/mbedTLS/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-Controller

clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-Controller:
	-$(RM) ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gap_aci.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_gatt_aci.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_hal_aci.su ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.d ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.o ./Middlewares/BlueNRG-2/Wireless/BlueNRG-2/Controller/bluenrg1_l2cap_aci.su

.PHONY: clean-Middlewares-2f-BlueNRG-2d-2-2f-Wireless-2f-BlueNRG-2d-2-2f-Controller

