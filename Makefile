CC=g++
CFLAGS=-I. -Wall -Wextra -Werror
DEPS = agency.h client.h travelpack.h address.h date.h StringFunctions.h files.h menu.h
OBJ = main.o agency.o client.o travelpack.o address.o date.o StringFunctions.o files.o menu.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all clean

clean:
	rm -f $(TARGETS) *.o *.d *.i *.s