
CSRBvfsOverlay: CSRBvfsOverlay.c
	gcc -Wall -fPIC -shared -o $@.so $< -ldl

.PHONY: clean
clean:
	rm -f CSRBvfsOverlay.so
