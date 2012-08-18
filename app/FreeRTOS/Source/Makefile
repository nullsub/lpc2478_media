
SRC_FILES=croutine.c list.c queue.c tasks.c

SUBDIRS=portable

#
# Define all object files.
#
ARM_OBJ = $(SRC_FILES:.c=.o)

.PHONY: all
ifeq ($(STARTEDATTOP),true)
all : subdirs $(ARM_OBJ)
else
all :
	@echo "Project must be rebuilt from top level"
endif

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

$(ARM_OBJ) : %.o : %.c Makefile .depend
	$(CC) -c $(CFLAGS) -Wno-cast-align -Wno-strict-aliasing $< -o $@
	$(AR) rc $(COMMON)/common.a $@

.depend:
	$(CC) $(CFLAGS) -M $(SRC_FILES) -o .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif
