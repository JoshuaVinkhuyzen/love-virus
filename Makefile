CC = gcc
SRC = src/main.c src/win32_helper.c
RES_OBJ = resource.o
OUT = love-virus.exe
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -luser32

build: $(RES_OBJ)
	$(CC) $(SRC) $(RES_OBJ) -o $(OUT) $(LIBS)

run: build
	./$(OUT)

release: $(RES_OBJ)
	$(CC) $(SRC) $(RES_OBJ) -o $(OUT) $(LIBS) -mwindows

$(RES_OBJ): resource.rc heart.ico
	windres resource.rc -O coff -o $(RES_OBJ)

clean:
	rm -f $(OUT) $(RES_OBJ)