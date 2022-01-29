bin/build/main.exec: bin/objects/main.o bin/objects/entity.o bin/objects/tileMap.o
	gcc bin/objects/*.o -o bin/build/main.exec -lSDL2main -lSDL2 -lSDL2_image
bin/objects/main.o: src/main.c
	gcc -c src/main.c -I include -o bin/objects/main.o
bin/objects/entity.o: src/entity.c
	gcc -c src/entity.c -I include -o bin/objects/entity.o
bin/objects/tileMap.o: src/tileMap.c
	gcc -c src/tileMap.c -I include -o bin/objects/tileMap.o