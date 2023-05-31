################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ApplicationsLayer/CenLoc/CenLoc.c 

OBJS += \
./ApplicationsLayer/CenLoc/CenLoc.o 

C_DEPS += \
./ApplicationsLayer/CenLoc/CenLoc.d 


# Each subdirectory must supply rules for building sources it contributes
ApplicationsLayer/CenLoc/%.o ApplicationsLayer/CenLoc/%.su: ../ApplicationsLayer/CenLoc/%.c ApplicationsLayer/CenLoc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"C:/Users/Daniel/Desktop/BMWI4_REPOSITORY/I4_BCC_WORKSPACE/I4_BCC/ApplicationsLayer/CenLoc" -I"C:/Users/Daniel/Desktop/BMWI4_REPOSITORY/I4_BCC_WORKSPACE/I4_BCC/ApplicationsLayer/ExtLights" -I"C:/Users/Daniel/Desktop/BMWI4_REPOSITORY/I4_BCC_WORKSPACE/I4_BCC/ApplicationsLayer/IntLights" -I"C:/Users/Daniel/Desktop/BMWI4_REPOSITORY/I4_BCC_WORKSPACE/I4_BCC/ApplicationsLayer/SecAlm" -I"C:/Users/Daniel/Desktop/BMWI4_REPOSITORY/I4_BCC_WORKSPACE/I4_BCC/ProjectIncludes" -I../Core/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Daniel/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ApplicationsLayer-2f-CenLoc

clean-ApplicationsLayer-2f-CenLoc:
	-$(RM) ./ApplicationsLayer/CenLoc/CenLoc.d ./ApplicationsLayer/CenLoc/CenLoc.o ./ApplicationsLayer/CenLoc/CenLoc.su

.PHONY: clean-ApplicationsLayer-2f-CenLoc
