################################################################################
# Automatically-generated file. Do not edit!
################################################################################


RM := rm -rf

# All of the sources participating in the build are defined here
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

O_SRCS := 
C_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
OBJS := 
C_DEPS := 
EXECUTABLES := 

# Every subdirectory with source files must be described here
SUBDIRS := \
. \
Log \
FuncionesPropias \

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Log/manejo_log.c 

OBJS += \
./Log/manejo_log.o 

C_DEPS += \
./Log/manejo_log.d 


# Each subdirectory must supply rules for building sources it contributes
Log/%.o: ../Log/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FuncionesPropias/manejo_archivos.c \
../FuncionesPropias/manejo_mensajes.c 

OBJS += \
./FuncionesPropias/manejo_archivos.o \
./FuncionesPropias/manejo_mensajes.o 

C_DEPS += \
./FuncionesPropias/manejo_archivos.d \
./FuncionesPropias/manejo_mensajes.d 


# Each subdirectory must supply rules for building sources it contributes
FuncionesPropias/%.o: ../FuncionesPropias/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pi.c 

OBJS += \
./pi.o 

C_DEPS += \
./pi.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

USER_OBJS :=

LIBS :=


ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TP2-PROCER-PI

# Tool invocations
TP2-PROCER-PI: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "TP2-PROCER-PI" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) TP2-PROCER-PI
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
