
SRC_FILES=port.c portISR.c

#
# Define all object files.
#
ARM_OBJ = $(SRC_FILES:.c=.o)

.PHONY: all
ifeq ($(STARTEDATTOP),true)
all: $(ARM_OBJ)
else
all :
	@echo "Project must be rebuilt from top level"
endif

$(ARM_OBJ) : %.o : %.c Makefile .depend
	$(CC) -c $(CFLAGS) $< -o $@
	$(AR) rc $(COMMON)/common.a $@


.depend:
	$(CC) $(CFLAGS) -M $(SRC_FILES) -o .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
