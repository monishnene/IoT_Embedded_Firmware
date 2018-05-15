################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.c 

OBJS += \
./platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.o 

C_DEPS += \
./platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.d 


# Each subdirectory must supply rules for building sources it contributes
platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.o: ../platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-D__HEAP_SIZE=0xD00' '-D__STACK_SIZE=0x800' '-DHAL_CONFIG=1' '-DEFR32BG1B232F256GM56=1' -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\lcd" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\src" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\CMSIS\Include" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emlib\inc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emlib\src" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\hardware\kit\common\bsp" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\hardware\kit\common\drivers" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\tempdrv\inc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\bootloader\api" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\hardware\kit\EFR32BG1_BRD4302A\config" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\sleep\src" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\radio\rail_lib\common" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\uartdrv\inc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\Device\SiliconLabs\EFR32BG1B\Source" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\hardware\kit\common\halconfig" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\common\inc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\app\bluetooth\common\stack_bridge" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\radio\rail_lib\chip\efr32" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\halconfig\inc\hal-config" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\tempdrv\src" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\emdrv\sleep\inc" -I"C:\Users\monis\SimplicityStudio\v4_workspace\Monish_Persistent_Memory\platform\bootloader" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.d" -MT"platform/Device/SiliconLabs/EFR32BG1B/Source/system_efr32bg1b.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


