# Generic Makefile for Atmel Start projects

################################################################################
# Project configuration (edit if you add directories)
################################################################################

# List the subdirectories for project source and header files
PROJ_SRC_DIRS := \
src

PROJ_INCLUDE_DIRS := \
src

# Specify the dir for the ASF library
ASF_DIR := asf-samd21

# List the subdirectories for Atmel source and header files
# Copy this directly from SUB_DIRS in $(ASF_DIR)/gcc/Makefile,
# but make sure to add ./
ATMEL_SRC_DIRS :=  \
./ \
hpl/systick \
hpl/dmac \
hal/src \
samd21a/gcc \
hpl/pm \
hpl/sysctrl \
hal/utils/src \
examples \
hpl/gclk \
samd21a/gcc/gcc \
hpl/core

# Add these based on DIR_INCLUDES in $(ASF_DIR)/gcc/Makefile,
# by copying it here and replacing '-I"../' with '' (nothing),
# making sure to include ./
# Alternatively, derive this based on ATMEL_SRC_DIRS above
# if DIR_INCLUDES doesn't exist
ATMEL_INCLUDE_DIRS := \
./ \
config \
examples \
hal/include \
hal/utils/include  \
hpl/core  \
hpl/dmac  \
hpl/gclk  \
hpl/pm  \
hpl/port  \
hpl/sysctrl  \
hpl/systick  \
hri  \
CMSIS/Include  \
samd21a/include  \

# Top-level directories make should look for things in
vpath %.c src/ $(ASF_DIR)/
vpath %.s src/ $(ASF_DIR)/
vpath %.S src/ $(ASF_DIR)/

############# Misc configuration #############
# CHANGE ME
OUTPUT_FILES_PREFIX := build/bse-fsw-template
OBJ_DIR := obj
GCC_ARGS := -x c -mthumb -DDEBUG -O0 -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99

############# Device configuration #############
# not sure if changing these will work
DEVICE_LINKER_SCRIPT := $(ASF_DIR)/samd21a/gcc/gcc/samd21j18a_flash.ld
MCPU := cortex-m0plus
DEVICE_FLAG := __SAMD21J18A__

################################################################################
# Variable generation. Do not edit unless you know what you're doing!
################################################################################

# Prefix atmel dirs with root dir
ATMEL_SRC_DIRS_FULL 	:= $(addprefix $(ASF_DIR)/, $(ATMEL_SRC_DIRS))
ATMEL_INCLUDE_DIRS_FULL := $(addprefix $(ASF_DIR)/, $(ATMEL_INCLUDE_DIRS))

# Find all source files in the directories
ALL_SRC_DIRS := $(PROJ_SRC_DIRS) $(ATMEL_SRC_DIRS_FULL)
SRCS  := $(foreach dr, $(ALL_SRC_DIRS), $(wildcard $(dr)/*.[csS]))
# Create all names of all corresponding object files
OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRCS))))
OBJS_AS_ARGS := $(foreach ob, $(OBJS), "$(ob)")
# Create all names of all corresponding dependency files
DEPS := $(OBJS:%.o=%.d)
DEPS_AS_ARGS := $(foreach dep, $(DEPS), "$(dep)")

# List the include files as linker args
ALL_INCLUDE_DIRS := $(PROJ_INCLUDE_DIRS) $(ATMEL_INCLUDE_DIRS_FULL)
INCLUDE_DIRS_AS_FLAGS := $(foreach dir, $(ALL_INCLUDE_DIRS), -I"$(dir)")

# Outputs
OUTPUT_FILE_PATH += $(OUTPUT_FILES_PREFIX).elf
OUTPUT_FILE_PATH_AS_ARGS += $(OUTPUT_FILE_PATH)

################################################################################
# Makefile targets. Do not edit unless you know what you're doing!
################################################################################
GCC := "arm-none-eabi-gcc"
GCC_ARGS += -D$(DEVICE_FLAG) -mcpu=$(MCPU)
LINKER_ARGS += 

ifdef SystemRoot
	SHELL = cmd.exe
	MK_DIR = mkdir
else
	MK_DIR = mkdir -p
endif

# All Target
all: $(ALL_DIRS) $(OUTPUT_FILE_PATH) $(OBJS)

$(ALL_DIRS):
	$(MK_DIR) "$@"

# Linker target
$(OUTPUT_FILE_PATH): $(OBJS)
	@echo Linking target: $@
	@mkdir -p $(dir $@)
	$(GCC) -o $(OUTPUT_FILES_PREFIX).elf $(OBJS_AS_ARGS) \
		-Wl,--start-group -lm -Wl,--end-group -mthumb \
		-Wl,-Map="$(OUTPUT_FILES_PREFIX).map" --specs=nano.specs -Wl,--gc-sections -mcpu=$(MCPU) \
	 	$(INCLUDE_DIRS_AS_FLAGS) \
		-T"$(DEVICE_LINKER_SCRIPT)" \
		-L"$(basename $(DEVICE_LINKER_SCRIPT))"
	@echo Finished building target: $@

	"arm-none-eabi-objcopy" -O binary "$(OUTPUT_FILES_PREFIX).elf" "$(OUTPUT_FILES_PREFIX).bin"
	"arm-none-eabi-objcopy" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  \
        "$(OUTPUT_FILES_PREFIX).elf" "$(OUTPUT_FILES_PREFIX).hex"
	"arm-none-eabi-objcopy" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma \
        .eeprom=0 --no-change-warnings -O binary "$(OUTPUT_FILES_PREFIX).elf" \
        "$(OUTPUT_FILES_PREFIX).eep" || exit 0
	"arm-none-eabi-objdump" -h -S "$(OUTPUT_FILES_PREFIX).elf" > "$(OUTPUT_FILES_PREFIX).lss"
	"arm-none-eabi-size" "$(OUTPUT_FILES_PREFIX).elf"

# Compiler target
$(OBJ_DIR)/%.o: %.[csS]
	@echo Building file: $<
	@mkdir -p $(dir $@)
	$(GCC) $(GCC_ARGS) $(INCLUDE_DIRS_AS_FLAGS) \
		-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -o "$@" "$<"
	@echo Finished building: $<

# Detect changes in the dependent files and recompile the respective object files.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

connect:
	@echo Make sure openocd is running!
	arm-none-eabi-gdb -iex "target extended-remote localhost:3333" $(OUTPUT_FILE_PATH)

clean:
	rm -f $(OBJS_AS_ARGS)
	rm -f $(OUTPUT_FILE_PATH)
	rm -f $(DEPS_AS_ARGS)
	rm -rf $(OBJ_DIR)
	rm -f $(OUTPUT_FILES_PREFIX).a $(OUTPUT_FILES_PREFIX).hex $(OUTPUT_FILES_PREFIX).bin \
        $(OUTPUT_FILES_PREFIX).lss $(OUTPUT_FILES_PREFIX).eep $(OUTPUT_FILES_PREFIX).map \
        $(OUTPUT_FILES_PREFIX).srec
