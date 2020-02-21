
################################################################################
# Automatically-generated file. Do not edit!
################################################################################

ifdef SystemRoot
	SHELL = cmd.exe
	MK_DIR = mkdir
else
	ifeq ($(shell uname), Linux)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), CYGWIN)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), MINGW32)
		MK_DIR = mkdir -p
	endif

	ifeq ($(shell uname | cut -d _ -f 1), MINGW64)
		MK_DIR = mkdir -p
	endif
endif

# List the subdirectories for creating object files
SUB_DIRS +=  \
 \
hpl/adc \
hpl/tc \
samd21a/armcc/Device/SAMD21A/Source/ARM \
hpl/systick \
hpl/dmac \
hal/src \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/MemMang \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0 \
hpl/pm \
samd21a/armcc/Device/SAMD21A/Source \
hpl/sysctrl \
hal/utils/src \
hpl/sercom \
examples \
hpl/gclk \
hpl/wdt \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0 \
hpl/core

# List the object files
OBJS +=  \
hal/src/hal_io.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/list.o \
hpl/systick/hpl_systick.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/event_groups.o \
hpl/wdt/hpl_wdt.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/croutine.o \
hal/utils/src/utils_event.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/stream_buffer.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/MemMang/heap_1.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/queue.o \
hal/src/hal_pwm.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/timers.o \
hal/src/hal_delay.o \
samd21a/armcc/Device/SAMD21A/Source/system_samd21.o \
hpl/pm/hpl_pm.o \
hpl/core/hpl_init.o \
hpl/gclk/hpl_gclk.o \
hal/src/hal_wdt.o \
hpl/core/hpl_core_m0plus_base.o \
hal/src/hal_usart_os.o \
hal/utils/src/utils_assert.o \
hpl/dmac/hpl_dmac.o \
hpl/sysctrl/hpl_sysctrl.o \
hal/src/hal_spi_m_os.o \
hal/src/hal_init.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/rtos_port.o \
rtos_start.o \
hal/utils/src/utils_list.o \
examples/driver_examples.o \
driver_init.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0/port.o \
samd21a/armcc/Device/SAMD21A/Source/ARM/startup_SAMD21.o \
hpl/sercom/hpl_sercom.o \
hal/utils/src/utils_ringbuffer.o \
main.o \
hal/src/hal_gpio.o \
hal/src/hal_i2c_m_os.o \
hal/src/hal_sleep.o \
hal/src/hal_adc_os.o \
atmel_start.o \
hpl/tc/hpl_tc.o \
hal/src/hal_atomic.o \
thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/tasks.o \
hpl/adc/hpl_adc.o

OBJS_AS_ARGS +=  \
"hal/src/hal_io.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/list.o" \
"hpl/systick/hpl_systick.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/event_groups.o" \
"hpl/wdt/hpl_wdt.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/croutine.o" \
"hal/utils/src/utils_event.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/stream_buffer.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/MemMang/heap_1.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/queue.o" \
"hal/src/hal_pwm.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/timers.o" \
"hal/src/hal_delay.o" \
"samd21a/armcc/Device/SAMD21A/Source/system_samd21.o" \
"hpl/pm/hpl_pm.o" \
"hpl/core/hpl_init.o" \
"hpl/gclk/hpl_gclk.o" \
"hal/src/hal_wdt.o" \
"hpl/core/hpl_core_m0plus_base.o" \
"hal/src/hal_usart_os.o" \
"hal/utils/src/utils_assert.o" \
"hpl/dmac/hpl_dmac.o" \
"hpl/sysctrl/hpl_sysctrl.o" \
"hal/src/hal_spi_m_os.o" \
"hal/src/hal_init.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/rtos_port.o" \
"rtos_start.o" \
"hal/utils/src/utils_list.o" \
"examples/driver_examples.o" \
"driver_init.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0/port.o" \
"samd21a/armcc/Device/SAMD21A/Source/ARM/startup_SAMD21.o" \
"hpl/sercom/hpl_sercom.o" \
"hal/utils/src/utils_ringbuffer.o" \
"main.o" \
"hal/src/hal_gpio.o" \
"hal/src/hal_i2c_m_os.o" \
"hal/src/hal_sleep.o" \
"hal/src/hal_adc_os.o" \
"atmel_start.o" \
"hpl/tc/hpl_tc.o" \
"hal/src/hal_atomic.o" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/tasks.o" \
"hpl/adc/hpl_adc.o"

# List the dependency files
DEPS := $(OBJS:%.o=%.d)

DEPS_AS_ARGS +=  \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/event_groups.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/croutine.d" \
"hpl/wdt/hpl_wdt.d" \
"hal/src/hal_i2c_m_os.d" \
"hal/src/hal_io.d" \
"hpl/gclk/hpl_gclk.d" \
"hpl/systick/hpl_systick.d" \
"main.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/timers.d" \
"hal/utils/src/utils_event.d" \
"samd21a/armcc/Device/SAMD21A/Source/system_samd21.d" \
"hal/src/hal_pwm.d" \
"hal/src/hal_usart_os.d" \
"hpl/core/hpl_core_m0plus_base.d" \
"hal/src/hal_wdt.d" \
"hpl/dmac/hpl_dmac.d" \
"hal/utils/src/utils_assert.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/stream_buffer.d" \
"hal/src/hal_delay.d" \
"hpl/core/hpl_init.d" \
"hpl/sysctrl/hpl_sysctrl.d" \
"hal/src/hal_spi_m_os.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/rtos_port.d" \
"hal/src/hal_init.d" \
"driver_init.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/MemMang/heap_1.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0/port.d" \
"rtos_start.d" \
"examples/driver_examples.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/list.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/queue.d" \
"hal/src/hal_adc_os.d" \
"hal/utils/src/utils_list.d" \
"hal/src/hal_sleep.d" \
"hal/utils/src/utils_ringbuffer.d" \
"hpl/sercom/hpl_sercom.d" \
"samd21a/armcc/Device/SAMD21A/Source/ARM/startup_SAMD21.d" \
"hal/src/hal_gpio.d" \
"hal/src/hal_atomic.d" \
"hpl/tc/hpl_tc.d" \
"hpl/pm/hpl_pm.d" \
"hpl/adc/hpl_adc.d" \
"thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/tasks.d" \
"atmel_start.d"

OUTPUT_FILE_NAME :=AtmelStart
QUOTE := "
OUTPUT_FILE_PATH +=$(OUTPUT_FILE_NAME).elf
OUTPUT_FILE_PATH_AS_ARGS +=$(OUTPUT_FILE_NAME).elf

vpath %.c ../
vpath %.s ../
vpath %.S ../

# All Target
all: $(SUB_DIRS) $(OUTPUT_FILE_PATH)

# Linker target

$(OUTPUT_FILE_PATH): $(OBJS)
	@echo Building target: $@
	@echo Invoking: ARMCC Linker
	$(QUOTE)armlink$(QUOTE) --ro-base 0x00000000 --entry 0x00000000 --rw-base 0x20000000 --entry Reset_Handler --first __Vectors \
--strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols \
--info sizes --info totals --info unused --info veneers --list $(OUTPUT_FILE_NAME).map \
-o $(OUTPUT_FILE_NAME).elf --cpu Cortex-M0+ \
$(OBJS_AS_ARGS)

	@echo Finished building target: $@

# Compiler target(s)




%.o: %.c
	@echo Building file: $<
	@echo ARMCC Compiler
	$(QUOTE)armcc$(QUOTE) --c99 -c -DDEBUG -O1 -g --apcs=interwork --split_sections --cpu Cortex-M0+ -D__SAMD21J18A__ \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/adc" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/gclk" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/systick" -I"../hpl/tc" -I"../hpl/wdt" -I"../hri" -I"../" -I"../config" -I"../thirdparty/RTOS" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/module_config" -I"../" -I"../CMSIS/Core/Include" -I"../samd21a/include"  \
--depend "$@"  -o "$@" "$<"

	@echo Finished building: $<

%.o: %.s
	@echo Building file: $<
	@echo ARMCC Assembler
	$(QUOTE)armasm$(QUOTE) -g --apcs=interwork --cpu Cortex-M0+ --pd "D__SAMD21J18A__ SETA 1" \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/adc" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/gclk" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/systick" -I"../hpl/tc" -I"../hpl/wdt" -I"../hri" -I"../" -I"../config" -I"../thirdparty/RTOS" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/module_config" -I"../" -I"../CMSIS/Core/Include" -I"../samd21a/include"  \
--depend "$(@:%.o=%.d)" -o "$@" "$<"

	@echo Finished building: $<

%.o: %.S
	@echo Building file: $<
	@echo ARMCC Preprocessing Assembler
	$(QUOTE)armcc$(QUOTE) --c99 -c -DDEBUG -O1 -g --apcs=interwork --split_sections --cpu Cortex-M0+ -D__SAMD21J18A__ \
-I"../" -I"../config" -I"../examples" -I"../hal/include" -I"../hal/utils/include" -I"../hpl/adc" -I"../hpl/core" -I"../hpl/dmac" -I"../hpl/gclk" -I"../hpl/pm" -I"../hpl/port" -I"../hpl/sercom" -I"../hpl/sysctrl" -I"../hpl/systick" -I"../hpl/tc" -I"../hpl/wdt" -I"../hri" -I"../" -I"../config" -I"../thirdparty/RTOS" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/portable/RVDS/ARM_CM0" -I"../thirdparty/RTOS/freertos/FreeRTOSV10.0.0/module_config" -I"../" -I"../CMSIS/Core/Include" -I"../samd21a/include"  \
--depend "$@"  -o "$@" "$<"

	@echo Finished building: $<

# Detect changes in the dependent files and recompile the respective object files.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

$(SUB_DIRS):
	$(MK_DIR) "$@"

clean:
	rm -f $(OBJS_AS_ARGS)
	rm -f $(OUTPUT_FILE_PATH)
	rm -f $(DEPS_AS_ARGS)
	rm -f $(OUTPUT_FILE_NAME).map $(OUTPUT_FILE_NAME).elf
