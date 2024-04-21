################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/hello_world.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/hello_world.d \
./source/semihost_hardfault.d 

OBJS += \
./source/hello_world.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DFRDM_K66F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/utilities" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/drivers" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/device" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/component/uart" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/component/lists" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/CMSIS" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/source" -I"/Users/cameron.beneteau/Documents/MCUXpressoIDE_11.9.0_2144/workspace/lab0-bare-metal-applications-group-10/frdmk66f_problem_5/board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/hello_world.d ./source/hello_world.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source
