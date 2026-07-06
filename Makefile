CC = gcc
SRC = src/main.c src/win32_helper.c
OUT = game.exe
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -luser32

build:
	$(CC) $(SRC) -o $(OUT) $(LIBS)

run: build
	./$(OUT)

clean:
	rm -f $(OUT)