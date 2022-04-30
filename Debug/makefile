################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./startup_msp432p401r_ccs.obj" \
"./system_msp432p401r.obj" \
"./Devices/MSPIO.obj" \
"./Hardware/CS_Driver.obj" \
"./Hardware/GPIO_Driver.obj" \
"./Hardware/SPI_Driver.obj" \
"./Hardware/TIMERA_Driver.obj" \
"./Hardware/UART_Driver.obj" \
"./fatfs/diskio.obj" \
"./fatfs/ff.obj" \
"./fatfs/ffsystem.obj" \
"./fatfs/ffunicode.obj" \
"./fatfs/mmc_MSP432P401r.obj" \
"./src/buzzer.obj" \
"./src/keypad.obj" \
"./src/lcd.obj" \
"./src/mfrc522.obj" \
"./src/port.obj" \
"./src/pwm.obj" \
"./src/rtc.obj" \
"./src/sd_card.obj" \
"./src/test.obj" \
"./src/ti_drivers_config.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Devices/subdir_vars.mk
-include Hardware/subdir_vars.mk
-include fatfs/subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include Devices/subdir_rules.mk
-include Hardware/subdir_rules.mk
-include fatfs/subdir_rules.mk
-include src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.out \

EXE_OUTPUTS__QUOTED += \
"Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.out" \

BIN_OUTPUTS += \
Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.hex \

BIN_OUTPUTS__QUOTED += \
"Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.out"

# Tool invocations
Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.map" --heap_size=1024 --stack_size=512 -i"C:/ti/ccs1120/ccs/ccs_base/arm/include" -i"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" -i"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/lib" -i"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols_linkInfo.xml" --rom_model -o "Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs1120/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armhex" --memwidth=8 --romwidth=8 --diag_wrap=off -o "Dual_Way_Security_and_data_logging_system_using_RFID_and_SPI_protocols.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "startup_msp432p401r_ccs.obj" "system_msp432p401r.obj" "Devices\MSPIO.obj" "Hardware\CS_Driver.obj" "Hardware\GPIO_Driver.obj" "Hardware\SPI_Driver.obj" "Hardware\TIMERA_Driver.obj" "Hardware\UART_Driver.obj" "fatfs\diskio.obj" "fatfs\ff.obj" "fatfs\ffsystem.obj" "fatfs\ffunicode.obj" "fatfs\mmc_MSP432P401r.obj" "src\buzzer.obj" "src\keypad.obj" "src\lcd.obj" "src\mfrc522.obj" "src\port.obj" "src\pwm.obj" "src\rtc.obj" "src\sd_card.obj" "src\test.obj" "src\ti_drivers_config.obj" 
	-$(RM) "main.d" "startup_msp432p401r_ccs.d" "system_msp432p401r.d" "Devices\MSPIO.d" "Hardware\CS_Driver.d" "Hardware\GPIO_Driver.d" "Hardware\SPI_Driver.d" "Hardware\TIMERA_Driver.d" "Hardware\UART_Driver.d" "fatfs\diskio.d" "fatfs\ff.d" "fatfs\ffsystem.d" "fatfs\ffunicode.d" "fatfs\mmc_MSP432P401r.d" "src\buzzer.d" "src\keypad.d" "src\lcd.d" "src\mfrc522.d" "src\port.d" "src\pwm.d" "src\rtc.d" "src\sd_card.d" "src\test.d" "src\ti_drivers_config.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

