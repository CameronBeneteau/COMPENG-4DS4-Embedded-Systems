################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/gpio_led_output.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/gpio_led_output.d \
./source/semihost_hardfault.d 

OBJS += \
./source/gpio_led_output.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/source" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/utilities" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/drivers" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/device" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/component/uart" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/component/lists" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/CMSIS" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/board" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_3/frdmk66f/driver_examples/gpio/led_output" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/gpio_led_output.d ./source/gpio_led_output.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

