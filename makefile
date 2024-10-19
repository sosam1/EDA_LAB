all: main.o empresa.o cargo.o
	g++ -o main main.o empresa.o cargo.o
main.o: main.c
	g++ -c main.c
empresa.o: empresa.h empresa.c
	g++ -c empresa.c
cargo.o: cargo.h cargo.c
	g++ -c cargo.c
clean:
	rm *.o
	rm main
