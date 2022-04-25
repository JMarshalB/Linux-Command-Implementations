all: myls mysearch mystat mytail

myls: myls-Jaylen.c
	gcc -o myls myls-Jaylen.c

mysearch: mysearch-Jaylen.c
	gcc -o mysearch mysearch-Jaylen.c

mystat: mystat-Jaylen.c
	gcc -o mystat mystat-Jaylen.c

mytail: mytail-Jaylen.c
	gcc -o mytail mytail-Jaylen.c

clean:
	rm myls
	rm mystat
	rm mysearch
	rm mytail


