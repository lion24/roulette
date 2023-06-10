CC = gcc
CFLAGS = -Wall
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
EXE = roulette

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
