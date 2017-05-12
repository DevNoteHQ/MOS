
FDIRS := $(shell find -maxdepth 1 -type d)
DIRS := $(patsubst ./%,%,$(FDIRS))
DIRSNBIN := $(patsubst .%,%,$(DIRS))
DIRSNDEB := $(filter-out Debug,$(DIRSNBIN))
MODULES := $(filter-out bin,$(DIRSNDEB))

.PHONY: all clean $(MODULES)

all: $(MODULES)

$(MODULES):
	rm -r -f Debug
	$(MAKE) -C $@
	@cp -R $(MODULES)/bin ./

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	rm -f -r bin
	mkdir bin
