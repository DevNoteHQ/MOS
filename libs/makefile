
IGNDIR = bin obj
FDIRS = $(shell find -maxdepth 1 -type d)
DIRS = $(patsubst ./%,%,$(FDIRS))
RDIRS = $(patsubst .%,%,$(DIRS))
MODULES = $(filter-out $(IGNDIR),$(RDIRS))

.PHONY: all clean $(MODULES)

all: $(MODULES)

$(MODULES):
	rm -r -f Debug
	rm -r -f obj
	$(MAKE) -C $@
	@cp -R $(MODULES)/bin ./

clean:
	$(foreach module,$(MODULES),$(MAKE) -C $(module) clean;)
	rm -r -f bin
	rm -r -f obj
	mkdir bin