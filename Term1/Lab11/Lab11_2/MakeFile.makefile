all: lab11_2

lab11_2: lab11_2.o functions.o utility.o
	g++ lab11_2.o functions.o utility.o -o lab11_2

lab11_2.o: lab11_2.c
	g++ -c lab11_2.c

utility.o: utility.c
	g++ -c utility.c
	
functions.o: functions.c
	g++ -c functions.c

clean:
	rm -rf *.o lab11_2