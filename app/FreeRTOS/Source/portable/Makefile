SUBDIRS=GCC MemMang

.PHONY: all
ifeq ($(STARTEDATTOP),true)
all : subdirs
else
all :
	@echo "Project must be rebuilt from top level"
endif

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
