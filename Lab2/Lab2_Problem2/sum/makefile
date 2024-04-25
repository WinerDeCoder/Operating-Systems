all: sum_multi sum_serial

sum_serial: sum_serial.c
	gcc -o sum_serial sum_serial.c -I.

sum_multi: sum_multi.c
	gcc -o sum_multi sum_multi.c -lpthread
	
.PHONY: clean
clean:
	rm -f sum_multi sum_serial
