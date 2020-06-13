CC = gcc
CFLAGS = -Wall
INFLAGS = -I../include
SRC = cfcGraph.c connexeGraph.c dfsGraph.c importGraph.c inverseGraph.c orientForteGraph.c
OBJ = $(SRC:.c=.o)
LIB = libgraph.a

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INFLAGS)

clean:
	rm -f $(LIB) $(OBJ)

.PHONY: clean
