################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IOServices/Dio/Dio.c 

OBJS += \
./IOServices/Dio/Dio.o 

C_DEPS += \
./IOServices/Dio/Dio.d 


# Each subdirectory must supply rules for building sources it contributes
IOServices/Dio/%.o IOServices/Dio/%.su: ../IOServices/Dio/%.c IOServices/Dio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"IOServices/Dio/Dio.c_includes.args"

clean: clean-IOServices-2f-Dio

clean-IOServices-2f-Dio:
	-$(RM) ./IOServices/Dio/Dio.d ./IOServices/Dio/Dio.o ./IOServices/Dio/Dio.su

.PHONY: clean-IOServices-2f-Dio

