
CSRBvfsOverlay: CSRBvfsOverlay.c
	#gcc -Wall -fPIC -shared -o $@.so $< -ldl
	gcc -W -Wall -fPIC -DPIC -c -o $@.o $< -ldl
	ld -shared -init=CSRBvfsOverlayInit -z initfirst $@.o -o $@.so

.PHONY: clean
clean:
	rm -f CSRBvfsOverlay.so
