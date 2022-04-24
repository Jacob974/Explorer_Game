bin/main.exe: bin/main.o bin/entity.o bin/tileMap.o
	gcc bin/*.o -o bin/main.exe -lSDL2main -lSDL2 -lSDL2_image
bin/main.o: src/main.c
	gcc -c src/main.c -O2 -I include -o bin/main.o
bin/entity.o: src/entity.c
	gcc -c src/entity.c -O2 -I include -o bin/entity.o
bin/tileMap.o: src/tileMap.c
	gcc -c src/tileMap.c -O2 -I include -o bin/tileMap.o
clean:
	rm bin/*.o