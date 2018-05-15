################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/emdrv/tempdrv/src/tempdrv.c 

OBJS += \
./platform/emdrv/tempdrv/src/tempdrv.o 

C_DEPS += \
./platform/emdrv/tempdrv/src/tempdrv.d 


# Each subdirectory must supply rules for building sources it contributes
platform/emdrv/tempdrv/src/tempdrv.o: ../platform/emdrv/tempdrv/src/tempdrv.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DHAL_CONFIG=1' '-DEFR32BG1B232F256GM56=1' -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\sleep\src" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emlib\inc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\hardware\kit\common\halconfig" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\protocol\bluetooth_2.7\ble_stack\inc\common" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\sleep\inc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\CMSIS\Include" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\hardware\kit\common\bsp" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\hardware\kit\common\drivers" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\radio\rail_lib\chip\efr32" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\hardware\kit\EFR32BG1_BRD4302A\config" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\uartdrv\inc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\halconfig\inc\hal-config" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emlib\src" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\gpiointerrupt\inc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\app\bluetooth_2.7\common\stack_bridge" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\Device\SiliconLabs\EFR32BG1B\Source" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\tempdrv\inc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\bootloader\api" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\radio\rail_lib\common" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\protocol\bluetooth_2.7\ble_stack\inc\soc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\tempdrv\src" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\emdrv\common\inc" -I"C:\SiliconLabs\SimplicityStudio\v4_3\Monish_Nene_OTA\platform\bootloader" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"platform/emdrv/tempdrv/src/tempdrv.d" -MT"platform/emdrv/tempdrv/src/tempdrv.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


