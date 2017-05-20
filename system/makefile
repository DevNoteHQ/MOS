
FDIRS := $(shell find -maxdepth 1 -type d)
DIRS := $(patsubst ./%,%,$(FDIRS))
DIRSNBIN := $(patsubst .%,%,$(DIRS))
DIRSNDEB := $(filter-out Debug,$(DIRSNBIN))
DIRSNOBJ := $(filter-out obj,$(DIRSNDEB))
DIRSNTRA := $(filter-out -,$(DIRSNOBJ))
MODULES := $(filter-out bin,$(DIRSNTRA))

.PHONY: all clean $(MODULES)

all: $(MODULES)

$(MODULES):
	rm -r -f Debug
	rm -r -f obj
	$(MAKE) -C $@
	@cp -R $(MODULES)/bin ./

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	rm -f -r bin
	mkdir bin
