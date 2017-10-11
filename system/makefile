
MODULES := kernel

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
