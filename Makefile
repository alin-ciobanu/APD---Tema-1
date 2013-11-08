
build:
	gcc -o serial serial.c
	gcc -o serial_optimizat serial_optimizat.c
	gcc -fopenmp -o paralel paralel.c

clean:
	rm -rf *o hellos
