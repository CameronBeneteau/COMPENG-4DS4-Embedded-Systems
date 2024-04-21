################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ecompass_peripheral.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/ecompass_peripheral.d \
./source/semihost_hardfault.d 

OBJS += \
./source/ecompass_peripheral.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_FLOAT_ENABLE=1 -DPRINTF_ADVANCED_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -DSDK_OS_BAREMETAL -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/utilities" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/drivers" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/accel" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/device" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/component/uart" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/component/lists" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/CMSIS" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/source" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/board" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/frdmk66f_lab_1_problem_5/frdmk66f/demo_apps/ecompass_peripheral" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ecompass_peripheral.d ./source/ecompass_peripheral.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

