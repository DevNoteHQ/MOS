
FDIRS := $(shell find -maxdepth 1 -type d)
DIRS := $(patsubst ./%,%,$(FDIRS))
RDIRS := $(patsubst .%,%,$(DIRS))
MODULES := $(filter-out bin,$(RDIRS))

.PHONY: all clean $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -C $@
	@cp -R $(MODULES)/bin ./

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	rm -f -r bin
	mkdir bin
