CC=g++
# CFLAGS=--std=c++11
SRC=src/ordo.cpp main.cpp
EXEC=bin/ordo
DIRS=bin

all: $(EXEC)

bin/ordo: src/ordo.cpp src/main.cpp
	$(CC) -o bin/ordo src/ordo.cpp src/main.cpp

clean:
	rm -rf bin

# will create all necessary directories after the Makefile is parsed
$(shell mkdir -p $(DIRS))
