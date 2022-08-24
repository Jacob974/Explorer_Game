CC=gcc
TARGET=main.exec
FLAGS= -Wall
INCLUDE=include
SRC=src

$(TARGET): bin/main.o bin/entity.o bin/tileMap.o makefile
	gcc bin/*.o -o $(TARGET) -lSDL2main -lSDL2 -lSDL2_image
bin/%.o: src/%.c 
	$(CC) $(FLAGS) -o $@ $^ -c -I $(INCLUDE)
clean:
	rm bin/*.o