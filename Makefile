.SILENT:

.PHONY: all
all: CSRBvfsOverlay.so

CSRBvfsOverlay.so: CSRBvfsOverlay.c
	echo Compiling $@
	gcc -W -Wall -fPIC \
		-I../../ -I../../../CSRBcore/ -I../../../SASnet/ \
		-Wl,-init,CSRBvfsOverlayInit -Wl,-z,initfirst -shared -o $@ $< -ldl
	#gcc -W -Wall -fPIC -DPIC -c -o $@.o $< -ldl
	#ld -shared -init=CSRBvfsOverlayInit -z initfirst $@.o -o $@.so

.PHONY: clean
clean:
	echo Cleaning
	rm -f CSRBvfsOverlay.so core.*

rebuild: clean all
