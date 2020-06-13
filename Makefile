CC = gcc
CFLAGS = -Wall
INFLAGS = -I./include
LIBFLAGS = -L./src -lgraph
SRC = analyzer/analyse.c
OBJ = $(SRC:.c=.o)
EXEC = graphAnalyzer

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

.PHONY: clean
