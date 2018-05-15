################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth_2.7/lib/EFR32BG1B/GCC/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/tempdrv/src/subdir.mk
-include platform/emdrv/sleep/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG1B/Source/GCC/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG1B/Source/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Monish_Nene_OTA.axf

# Tool invocations
Monish_Nene_OTA.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\efr32bg1b232f256gm56.ld" -Xlinker --gc-sections -Xlinker -Map="Monish_Nene_OTA.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o Monish_Nene_OTA.axf -Wl,--start-group "./application_properties.o" "./cmu.o" "./gatt_db.o" "./gpio.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./letimer_sleep.o" "./main.o" "./pti.o" "./temperature_i2c.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/drivers/mx25flash_spi.o" "./platform/Device/SiliconLabs/EFR32BG1B/Source/GCC/startup_efr32bg1b.o" "./platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.o" "./platform/emdrv/sleep/src/sleep.o" "./platform/emdrv/tempdrv/src/tempdrv.o" "./platform/emlib/src/em_acmp.o" "./platform/emlib/src/em_adc.o" "./platform/emlib/src/em_aes.o" "./platform/emlib/src/em_assert.o" "./platform/emlib/src/em_burtc.o" "./platform/emlib/src/em_can.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_core.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_crypto.o" "./platform/emlib/src/em_csen.o" "./platform/emlib/src/em_dac.o" "./platform/emlib/src/em_dbg.o" "./platform/emlib/src/em_dma.o" "./platform/emlib/src/em_ebi.o" "./platform/emlib/src/em_emu.o" "./platform/emlib/src/em_gpcrc.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_idac.o" "./platform/emlib/src/em_int.o" "./platform/emlib/src/em_lcd.o" "./platform/emlib/src/em_ldma.o" "./platform/emlib/src/em_lesense.o" "./platform/emlib/src/em_letimer.o" "./platform/emlib/src/em_leuart.o" "./platform/emlib/src/em_mpu.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_opamp.o" "./platform/emlib/src/em_pcnt.o" "./platform/emlib/src/em_prs.o" "./platform/emlib/src/em_qspi.o" "./platform/emlib/src/em_rmu.o" "./platform/emlib/src/em_rtc.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "./platform/emlib/src/em_vcmp.o" "./platform/emlib/src/em_vdac.o" "./platform/emlib/src/em_wdog.o" "C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\radio\rail_lib\autogen\librail_release\librail_efr32xg1_gcc_release.a" "C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\protocol\bluetooth_2.7\lib\EFR32BG1B\GCC\libbluetooth.a" "C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\protocol\bluetooth_2.7\lib\EFR32BG1B\GCC\libmbedtls.a" "C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\protocol\bluetooth_2.7\lib\EFR32BG1B\GCC\libpsstore.a" "C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\protocol\bluetooth_2.7\lib\EFR32BG1B\GCC\binapploader.o" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: Monish_Nene_OTA.hex'
	arm-none-eabi-objcopy -O ihex "Monish_Nene_OTA.axf" "Monish_Nene_OTA.hex"
	@echo ' '

	@echo 'Building bin file: Monish_Nene_OTA.bin'
	arm-none-eabi-objcopy -O binary "Monish_Nene_OTA.axf" "Monish_Nene_OTA.bin"
	@echo ' '

	@echo 'Building s37 file: Monish_Nene_OTA.s37'
	arm-none-eabi-objcopy -O srec "Monish_Nene_OTA.axf" "Monish_Nene_OTA.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "Monish_Nene_OTA.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Monish_Nene_OTA.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
