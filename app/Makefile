export PATH_TOOL= /home/chrisu/arm-cs-tools/bin/
export CC=$(PATH_TOOL)arm-none-eabi-gcc
export AR=$(PATH_TOOL)arm-none-eabi-ar
export OBJCOPY=$(PATH_TOOL)arm-none-eabi-objcopy
export OBJDUMP=$(PATH_TOOL)arm-none-eabi-objdump
export OBJNM=$(PATH_TOOL)arm-none-eabi-nm
export LDSCRIPT=ldscript-flash.ld
export CRT0=boot.s
export TARGET=SBC_lpc2478_v0.1
export LINKER_FLAGS=$(COMMON)/common.a -Xlinker -obuild/${TARGET}.elf -Xlinker -M -Xlinker -Map=build/${TARGET}.map  
export WARNINGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wsign-compare -Waggregate-return -Wstrict-prototypes -Wmissing-declarations
export CFLAGS=$(WARNINGS) -mlong-calls -D GCC_ARM7 $(INCLUDES) $(BASEINCLUDE) -mcpu=arm7tdmi -T$(LDSCRIPT) -O0 -g -fomit-frame-pointer -fno-common -std=gnu99
export ROOT=$(shell pwd)
export BASEINCLUDE=-I$(ROOT) -I$(ROOT)/FreeRTOS/Source/include
export COMMON=$(ROOT)/build/common
export STARTEDATTOP=true
 

SUBDIRS=FreeRTOS/Source

SRC_FILES += main.c
SRC_FILES += syscalls.c
SRC_FILES += leds.c
SRC_FILES += uart.c
SRC_FILES += terminal.c
SRC_FILES += tprintf.c

ARM_OBJ = $(SRC_FILES:.c=.o)

# List of all source files without directory and file-extension.
#ALLSRCBASE = $(notdir $(basename $(SRC_FILES)))
ARM_BUILD_OBJ     = $(addprefix build/, $(ARM_OBJ))

# Define all listing files (used for make clean).
#LSTFILES   = $(addprefix $(OUTDIR)/, $(addsuffix .lst, $(ALLSRCBASE)))J

.PHONY: all
all : subdirs build/$(TARGET).hex

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE)	-C	$@

build/$(TARGET).hex : .depend Makefile build/$(TARGET).elf
	$(OBJCOPY) build/$(TARGET).elf -O ihex build/$(TARGET).hex
	@echo "Length is " `grep __"end_of_text__ = ." build/*.map | cut -b 17-35` "bytes"

build/$(TARGET).elf : .depend Makefile $(ARM_OBJ) $(COMMON)/common.a $(CRT0) $(LDSCRIPT)
	$(CC) $(CFLAGS) $(ARM_BUILD_OBJ) -nostartfiles $(CRT0) $(LINKER_FLAGS)
	$(OBJDUMP) -d -S build/$(TARGET).elf >build/$(TARGET).lst
	$(OBJDUMP) -h -S -C build/$(TARGET).elf >build/$(TARGET).lss
	$(OBJNM) -n build/$(TARGET).elf >build/$(TARGET).sym
	
$(ARM_OBJ) : %.o : %.c Makefile .depend
	$(CC) -c $(CFLAGS) $< -o build/$@

#
#  The .depend files contains the list of header files that the
#  various source files depend on.  By doing this, we'll only
#  rebuild the .o's that are affected by header files changing.
#
.depend:
	$(CC) $(CFLAGS) -M $(SRC_FILES) -o .depend

#
#  Utility targets
#
#
flash:
	../flash_prog/lpc21isp -control build/$(TARGET).hex /dev/ttyUSB0 115200 12000


.PHONY: tags
tags :
	@rm -f tags ctags
	find . -name \*.c -exec ctags -a {} \;
	find . -name \*.h -exec ctags -a {} \;

.PHONY: clean
clean :
	find . -name \*.o -exec rm -f {} \;
	find . -name .depend -exec rm -f {} \;
	rm build/* -rf
	mkdir build/common


#
#
#
ifeq (.depend,$(wildcard .depend))
include .depend
endif
