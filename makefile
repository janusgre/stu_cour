CC=gcc
CFLAGS=-I./include
objects=./lib/stu.c ./lib/cour.c
main : $(objects) ./lib/libms.so
	$(CC) -g -o main main.c $(CFLAGS) -L./lib -lms
main.o : main.c
	$(CC) $(CFLAGS) -g -c main.c -o main.o
./lib/libms.so : $(objects)
	$(CC) -fPIC -shared $(CFLAGS) $(objects) -o ./lib/libms.so 
clean :
	rm -rf *.o main *.so *.a
