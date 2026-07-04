CC = gcc
SRC = src/main.c
OUT = game.exe
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

build:
	$(CC) $(SRC) -o $(OUT) $(LIBS)

run: build
	./$(OUT)

clean:
	rm -f $(OUT)