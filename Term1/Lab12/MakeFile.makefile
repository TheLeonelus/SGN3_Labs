all: lab12

lab12: lab12.o functions.o utility.o
	g++ lab12.o functions.o utility.o -o lab12

lab12.o: lab12.c
	g++ -c lab12.c

utility.o: utility.c
	g++ -c utility.c
	
functions.o: functions.c
	g++ -c functions.c

clean:
	rm -rf *.o lab12