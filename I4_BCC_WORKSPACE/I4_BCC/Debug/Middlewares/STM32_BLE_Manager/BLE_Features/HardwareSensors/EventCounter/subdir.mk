################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLEMGR/1.3.0/Middlewares/ST/STM32_BLE_Manager/Src/BLE_EventCounter.c 

OBJS += \
./Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.o 

C_DEPS += \
./Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.o: C:/Users/Daniel/STM32Cube/Repository/Packs/STMicroelectronics/X-CUBE-BLEMGR/1.3.0/Middlewares/ST/STM32_BLE_Manager/Src/BLE_EventCounter.c Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -DSTM32_THREAD_SAFE_STRATEGY=4 -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.c_includes.args"

clean: clean-Middlewares-2f-STM32_BLE_Manager-2f-BLE_Features-2f-HardwareSensors-2f-EventCounter

clean-Middlewares-2f-STM32_BLE_Manager-2f-BLE_Features-2f-HardwareSensors-2f-EventCounter:
	-$(RM) ./Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.d ./Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.o ./Middlewares/STM32_BLE_Manager/BLE_Features/HardwareSensors/EventCounter/BLE_EventCounter.su

.PHONY: clean-Middlewares-2f-STM32_BLE_Manager-2f-BLE_Features-2f-HardwareSensors-2f-EventCounter
