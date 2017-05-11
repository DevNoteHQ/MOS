
FDIRS = $(shell find -maxdepth 1 -type d)
DIRS = $(patsubst ./%,%,$(FDIRS))
MODULES := $(patsubst .%,%,$(DIRS))

.PHONY: all clean $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -C $@

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
