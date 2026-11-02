CC     = gcc
CFLAGS = -Wall -g
SRC    = main.c function.c addition.c subtraction.c multiplication.c division.c
OBJ    = $(SRC:.c=.o)
TARGET = APC.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c apc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
