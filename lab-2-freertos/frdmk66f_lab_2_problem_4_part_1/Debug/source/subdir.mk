################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/freertos_hello.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/freertos_hello.d \
./source/semihost_hardfault.d 

OBJS += \
./source/freertos_hello.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/source" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/drivers" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/device" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/utilities" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/component/uart" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/component/serial_manager" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/component/lists" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/CMSIS" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/freertos/freertos_kernel/include" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/freertos/freertos_kernel/portable/GCC/ARM_CM4F" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab2-freertos-group-10/frdmk66f_lab_2_problem_4_part_1/board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/freertos_hello.d ./source/freertos_hello.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

